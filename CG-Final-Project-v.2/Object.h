#pragma once
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "glsl.h"
#include "Animation.h"
#include <iostream>

class Object
{
	bool AllAnimationsFinished = false;

protected:
	bool loopAllAnimations = false;

	GLuint vao;


public:

	virtual void handleAnimations();

	bool rotating = false;

	glm::mat4 model;
	glm::vec4 rotation;
	unsigned short numberOfAnimations = 0;
	unsigned short currentAnimation = 0;
	vector<Animation> animations;

	//handels the rotating and the animating so the base classes can just implement this render function
	virtual void Render();

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

	virtual void setAnimations(const vector<Animation> animations, bool loopAll = false);

	virtual void setAnimation(Animation animation);

	virtual void AddAnimation(Animation animation);

	static void InitShaders(const char* vertex_shader_path, const char* frag_shader_path, GLuint* program_id)
	{
		char* vertexshader = glsl::readFile(vertex_shader_path);
		GLuint vsh_id = glsl::makeVertexShader(vertexshader);

		char* fragshader = glsl::readFile(frag_shader_path);
		GLuint fsh_id = glsl::makeFragmentShader(fragshader);

		(*program_id) = glsl::makeShaderProgram(vsh_id, fsh_id);
	}

	static Camera* camera;
};

