#pragma once

#include <glm/glm.hpp>;
#include "glsl.h"
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_mat.hpp>

class Keyframe
{
public:
	float time = 1;
	glm::vec3 translate = glm::vec3();
	glm::vec4 rotation = glm::vec4();
	glm::vec3 pivot = glm::vec3();
	glm::vec3 scale = glm::vec3();

	Keyframe() {};
	Keyframe(glm::vec3 _translate, float _time) : translate(_translate), time(_time) {};
	Keyframe(glm::vec4 _rotate, float _time, glm::vec3 _pivot = {}) : rotation(_rotate), time(_time), pivot(_pivot){};
};

