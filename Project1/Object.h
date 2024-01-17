#pragma once
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "glsl.h"
#include "Animation.h"
#include <iostream>

class Object
{
	bool loopAllAnimations = false;

protected:
	GLuint vao;
	vector<Animation> animations;

	virtual void handleAnimations() {
		//if there are no animations to handle
		if (numberOfAnimations <= 0) {
			return;
		}


		//if the animation isn't finished then just return
		if (!this->animations[currentAnimation].finished) {
			//apply the animation
			animations[currentAnimation].Apply(&model);
			return;
		}

		//check if the animation should be looped or not
		if (this->animations[currentAnimation].looped) {
			this->animations[currentAnimation].Restart();
		}
		else
		{
			//if not then go to the next animation if there is one
			if (currentAnimation + 1 < numberOfAnimations) {
				currentAnimation++;

				//restart the new animation to make shure the time is properly tracked
				animations[currentAnimation].Restart();
				return;
			}

			//if all the animations need to be looped than reset the animation counter and restart all animations
			if (loopAllAnimations) {
				currentAnimation = 0;
				for (int i = 0; i < numberOfAnimations; i++) {
					animations[i].Restart();
				}
			}
		}
	}

public:

	glm::mat4 model;
	glm::vec4 rotation;
	unsigned short numberOfAnimations = 0;
	unsigned short currentAnimation = 0;

	//handels the rotating and the animating so the base classes can just implement this render function
	virtual void Render() {

		if(rotation != glm::vec4(0))
		{
			model = glm::rotate(model, glm::radians(rotation.w), glm::vec3(rotation.x, rotation.y, rotation.z));
		}

		handleAnimations();
		 
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

	virtual void setAnimations(const vector<Animation> animations, bool loopAll = false) {
		numberOfAnimations = animations.size();
		
		this->animations = vector<Animation>();

		for (int i = 0; i < animations.size(); i++) {
			this->animations.push_back(animations[i]);
		}
		loopAllAnimations = loopAll;
	}

	virtual void setAnimation(const Animation animation) {
		numberOfAnimations = 1;
		this->animations = { animation };
	}

	virtual void AddAnimation(Animation animation) {
		this->animations.push_back(animation);
		numberOfAnimations++;
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
};

