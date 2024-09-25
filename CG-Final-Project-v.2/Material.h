#pragma once
#include <glm/detail/type_vec3.hpp>
struct Material
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float power;

	Material(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float pow) {
		ambient = amb;
		diffuse = diff;
		specular = spec;
		power = pow;
	}

	Material() {
		ambient = glm::vec3(1);
		diffuse = glm::vec3(0);
		specular = glm::vec3(0);
		power = 1;
	}
};

