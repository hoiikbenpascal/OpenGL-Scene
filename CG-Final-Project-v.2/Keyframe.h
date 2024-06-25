#pragma once

#include <glm/glm.hpp>;
#include "glsl.h"
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_mat.hpp>

class Keyframe
{
	glm::vec3 translate = glm::vec3();
	glm::vec4 rotation = glm::vec4();
	glm::vec3 pivot = glm::vec3();
	glm::vec3 scale = glm::vec3();

public:

	float time = 1;

	Keyframe()
	{
		time = -1;
	};

	Keyframe(float time) { this->time = time; };

	//create only movement
	Keyframe(glm::vec3 _translate, float _time) : translate(_translate), time(_time) {};

	//only rotation
	Keyframe(glm::vec4 _rotate, float _time, glm::vec3 _pivot = {}) : rotation(_rotate), time(_time), pivot(_pivot) {};

	//movement and rotation
	Keyframe(glm::vec3 _translate, glm::vec4 _rotate, float _time, glm::vec3 _pivot = {}) :
		translate(_translate), rotation(_rotate), time(_time), pivot(_pivot) {};

	//movement and rotation flipped translate and rotate
	Keyframe(glm::vec4 _rotate, glm::vec3 _translate, float _time, glm::vec3 _pivot = {}) :
		translate(_translate), rotation(_rotate), time(_time), pivot(_pivot) {};

	//don't think this is needed but did it anyway just to be sure
	Keyframe(const Keyframe& frame) {
		this->translate = frame.translate;
		this->rotation = frame.rotation;
		this->pivot = frame.pivot;
		this->scale = frame.scale;
		this->time = frame.time;
	}

	void Apply(glm::mat4* model, float delta_time);

	//made sure to use nodiscard and const to indicate it returns a new keyframe instead of altering itself
	[[nodiscard]] Keyframe flip() const {
		//flip around the rotation angle
		glm::vec4 temp_rotation = rotation;
		temp_rotation[3] = rotation[3] * -1;

		return Keyframe(translate * -1.0f, temp_rotation, time);
	}

	glm::vec4* GetRotation() {
		return &rotation;
	}

	glm::vec3* GetPivot() {
		return &pivot;
	}

	//also made a static function
	static Keyframe flip(const Keyframe* frame) {
		//flip around the rotation angle
		glm::vec4 temp_rotation = frame->rotation;
		temp_rotation[3] = frame->rotation[3] * -1;

		return Keyframe(frame->translate * -1.0f, temp_rotation, frame->time);
	}

	static void flip(Keyframe* frame) {
		frame->rotation[3] *= -1;
		frame->translate *= -1;
	}

};

