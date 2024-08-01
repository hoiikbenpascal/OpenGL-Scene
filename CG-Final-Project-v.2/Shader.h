#pragma once
#include "glsl.h"

class Shader
{
public:

	GLuint programId;

	Shader(std::string vertex_path, std::string fragment_path) {
		char* vertexshader = glsl::readFile(vertex_path.c_str());
		GLuint vsh_id = glsl::makeVertexShader(vertexshader);

		char* fragshader = glsl::readFile(fragment_path.c_str());
		GLuint fsh_id = glsl::makeFragmentShader(fragshader);

		programId = glsl::makeShaderProgram(vsh_id, fsh_id);
	}

	GLuint GetUniform(string uniform_name) {
		GLuint uniform_location = glGetUniformLocation(programId, uniform_name.c_str());
		if(uniform_location == -1)
		{
			throw "Failed to get uniform with name: " + uniform_name;
		}
	}

	void Activate() {
		glUseProgram(programId);
	}

	void Delete() {
		glDeleteProgram(programId);
	}

};

