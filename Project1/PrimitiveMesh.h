#pragma once
#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>

enum PrimitveTypes {
	Line = GL_LINES,
	Triangle = GL_TRIANGLES
};

class PrimitiveMesh : public Object
{
	int vertices_size, colors_size, indices_size;

	GLfloat* vertices;
	GLfloat* colors;
	GLushort* indices;

	PrimitveTypes type;

	glm::mat4 model = glm::mat4();

	static const char* vertex_shader_path;
	static const char* frag_shader_path;
	static GLuint uniform_mvp;
	static GLuint program_id;
	static bool shaders_made;

public:

	PrimitiveMesh(GLfloat vertices[], int vertices_size,
		GLfloat colors[] , int colors_size,
		GLushort indices[], int indices_size,
		PrimitveTypes type = Line);

	PrimitiveMesh();

	void ApplyModel(const glm::mat4* model) {
		this->model = *model * this->model;
	}

	glm::mat4 getModel() {
		return this->model;
	}


	void Render() override;
	void InitBuffers() override;
	void Scale(float x, float y, float z) override;
	void Move(float x, float y, float z) override;

};
