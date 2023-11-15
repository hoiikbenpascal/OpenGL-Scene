#pragma once
#include "Object.h"


class PrimitiveObject : public Object
{
	int vertices_size, colors_size, elements_size;

	GLfloat* vertices;
	GLfloat* colors;
	GLushort* elements;

	glm::mat4 model = glm::mat4();

	static const char* vertex_shader_path;
	static const char* frag_shader_path;
	static GLuint uniform_mvp;
	static GLuint program_id;
	static bool shaders_made;

public:

	PrimitiveObject(GLfloat vertices[], int vertices_size, GLfloat colors[] , int colors_size, GLushort elements[], int elements_size);
	PrimitiveObject();

	void Render() override;
	void InitBuffers() override;

	void Move(float x, float y, float z) override;

};

