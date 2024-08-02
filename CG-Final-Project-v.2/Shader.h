#pragma once
#include "glsl.h"
#include <glm/detail/type_mat.hpp>

class Shader
{
public:

	GLuint programId;

	Shader(std::string vertex_path, std::string fragment_path) {

		char* vertexshader = glsl::readFile(vertex_path.c_str());
		char* fragshader = glsl::readFile(fragment_path.c_str());


		GLuint vsh_id = glsl::makeVertexShader(vertexshader);
		GLuint fsh_id = glsl::makeFragmentShader(fragshader);
		programId = glsl::makeShaderProgram(vsh_id, fsh_id);
	}

	GLuint GetUniform(const char* uniform_name);

	void AddUniformsIfAvailable(const glm::mat4* model, const glm::mat4* view, const glm::mat4* projection);

	void Activate() {
		glUseProgram(programId);
	}

	void Delete() {
		glDeleteProgram(programId);
	}

};

