#pragma once
#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Texture_Class.h"

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

	vector<glm::vec2> uvs;
	int uv_scale = 1;

	PrimitveTypes type;



public:

	Texture* texture = nullptr;

	PrimitiveMesh(GLfloat* vertices, int vertices_size,
		GLfloat* colors, int colors_size,
		GLushort* indices, int indices_size,
		PrimitveTypes type = Line);

	PrimitiveMesh();

	~PrimitiveMesh() {
		delete[] vertices;
		delete[] indices;
		delete[] colors;
	}

	void ApplyModel(const glm::mat4* model) {
		this->model = *model * this->model;
	}

	void Render() override;
	void InitBuffers() override;

};
