#pragma once
#include <GL/glew.h>
#include <string>
#include "glsl.h"
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "Material.h"

class Shader
{
public:

	GLuint programId;

	Shader(std::string vertex_path, std::string fragment_path);
	Shader(std::string folder_path);

	GLuint GetUniform(const char* uniform_name);

	void SetStandardUniformsIfAvailable(const glm::mat4* model, const glm::mat4* view, const glm::mat4* projection);
	void SetMatUniformsIfAvailable(const glm::vec3 light_pos, const Material* mat);

	void Activate();

	void Delete() {
		glDeleteProgram(programId);
	}

};

