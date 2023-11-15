#pragma once
#include <glm/detail/type_mat.hpp>

#include "Camera.h"
#include "glsl.h"

class Object
{

protected:
	GLuint vao;
public:

	glm::vec4 rotation;

	virtual void Render() = 0;
	virtual void InitBuffers() = 0;

	virtual	void Move(float x, float y, float z) = 0;

	bool rotating = false;

	void SetRotation(float x, float y, float z, float angle);

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

