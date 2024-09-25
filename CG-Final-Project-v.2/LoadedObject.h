#pragma once
#include <vector>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/detail/type_vec3.hpp>

#include "Object.h"
#include "Texture_Class.h"

#define amb_diff_spec_size 3

class LoadedObject : public Object
{

	vector<glm::vec3> normals;
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	glm::vec3 delta_position;
	Texture texture = NULL;


	glm::vec3 amb_diff_spec[amb_diff_spec_size];
	float power;

	bool apply_texture = false;

public:
	void Render() override;
	void InitBuffers() override;

	LoadedObject(const char object_path[], const Material* mat = nullptr, const char texture_path[] = nullptr);
	//LoadedObject(){};
};
