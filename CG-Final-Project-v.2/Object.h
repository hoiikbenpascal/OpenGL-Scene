#pragma once
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "glsl.h"
#include "Animation.h"
#include <iostream>
#include "Shader.h"
#include "Material.h"

class Object
{
	bool AllAnimationsFinished = false;

protected:

	bool loopAllAnimations = false;
	GLuint vao;
	Shader* shader = nullptr;

	Material mat = Material();

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

	virtual void SetShaders(Shader* shader) {
		this->shader = shader;
	}

	virtual void SetMat(Material* mat) {
		this->mat = *mat;
	}

	virtual	void Move(float x, float y, float z) {
		model = glm::translate(model, glm::vec3(x, y, z));
	}

	virtual void Rotate(float x, float y, float z, float angle) {
		angle = glm::radians(angle);
		model = glm::rotate(model, angle, glm::vec3(x, y, z));
	};

	virtual void Rotate(glm::vec3 axis, float angle, glm::vec3 pivot) {
		angle = glm::radians(angle);

		model = glm::translate(model, pivot);
		model = glm::rotate(model, angle, axis);
		model = glm::translate(model, -pivot);
	}

	virtual void Rotate(glm::vec3 rotation, float radian) {
		model = glm::rotate(model, radian, rotation);
	}

	virtual void Scale(float x, float y, float z) {
		model = glm::scale(model, glm::vec3(x, y, z));
	};

	virtual void setAnimations(const vector<Animation> animations, bool loopAll = false);

	virtual void setAnimation(Animation animation);

	virtual void AddAnimation(Animation animation);

	static Camera* camera;
};

