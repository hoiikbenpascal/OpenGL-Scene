#pragma once
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "glsl.h"
#include "Animation.h"
#include <iostream>

class Object
{

protected:
	GLuint vao;
public:

	glm::mat4 model;
	glm::vec4 rotation;
	Animation* animations;
	unsigned short numberOfAnimations = 0;
	unsigned short currentAnimation = 0;

	//handels the rotating and the animating so the base classes can just implement this render function
	virtual void Render() {

		if (numberOfAnimations > 0) {
			animations[currentAnimation].Apply(&model);
			if (this->animations[currentAnimation].finished) {
				this->animations[currentAnimation].Restart();
			}
		}

		if(rotation != glm::vec4(0))
		{
			model = glm::rotate(model, glm::radians(rotation.w), glm::vec3(rotation.x, rotation.y, rotation.z));
		}

	};

	virtual void InitBuffers() = 0;

	virtual	void Move(float x, float y, float z) {
		model = glm::translate(model, glm::vec3(x, y, z));
	}

	virtual void Rotate(float x, float y, float z, float angle) {
		angle = glm::radians(angle);
		model = glm::rotate(model, angle, glm::vec3(x, y, z));
	};

	virtual void Scale(float x, float y, float z) {
		model = glm::scale(model, glm::vec3(x, y, z));
	};

	virtual void setAnimations(const Animation* animations, int number) {
		this->animations = (Animation*) calloc(number, sizeof(Animation));
		numberOfAnimations = number;

		if (this->animations == nullptr) {
			throw std::bad_alloc();
		}

		for (int i = 0; i < number; i++) {
			this->animations[i] = animations[i];
		}

	}

	bool rotating = false;

	virtual void SetRotation(float x, float y, float z, float angle)
	{
		if (x, y, z, angle == 0)
		{
			rotating = false;
			return;
		}
		this->rotation = glm::vec4(x, y, z, angle);
		rotating = true;
	};

	static void InitShaders(const char* vertex_shader_path,const char* frag_shader_path, GLuint* program_id)
	{
		char* vertexshader = glsl::readFile(vertex_shader_path);
		GLuint vsh_id = glsl::makeVertexShader(vertexshader);

		char* fragshader = glsl::readFile(frag_shader_path);
		GLuint fsh_id = glsl::makeFragmentShader(fragshader);

		(*program_id) = glsl::makeShaderProgram(vsh_id, fsh_id);
	}

	static Camera* camera;

	~Object() {
		delete[] animations;
	}
};

