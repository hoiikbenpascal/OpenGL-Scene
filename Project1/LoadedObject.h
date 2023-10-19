#pragma once
#include <vector>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/detail/type_vec3.hpp>

#include "Object.h"

#define amb_diff_spec_size 3

class LoadedObject : public Object
{

	vector<glm::vec3> normals;
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	GLuint texture_id;


	glm::vec3 amb_diff_spec[amb_diff_spec_size];
	glm::mat4 model;
	float power;

public:
	void Render() override;
	void InitBuffers() override;
	LoadedObject(const char object_path[], float power = 1, glm::vec3 amb_diff_spec[] = nullptr, const char texture_path[] = nullptr);
	LoadedObject(){};

	static const char* vertexShaderPath;
	static const char* fragShaderPath;

	static GLuint program_id;
	static GLuint uniform_proj;
	static GLuint uniform_material_ambient;
	static GLuint uniform_material_diffuse;
	static GLuint uniform_specular;
	static GLuint uniform_material_power;
	static GLuint uniform_mv;
};
