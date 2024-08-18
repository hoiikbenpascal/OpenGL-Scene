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
protected:

	int vertices_size, colors_size = 0, indices_size;

	GLfloat* vertices;
	GLfloat* colors;
	GLushort* indices;


	PrimitveTypes type;

public:

	vector<glm::vec2> uvs;

	Texture* texture = nullptr;

	PrimitiveMesh(GLfloat* vertices, int vertices_size,
		GLushort* indices, int indices_size,
		GLfloat* colors, int colors_size,
		PrimitveTypes type = Line);

	PrimitiveMesh(GLfloat* vertices, int vertices_size, GLushort* indices, int indices_size, PrimitveTypes type);

	PrimitiveMesh() {};

	~PrimitiveMesh() {
		if (vertices != nullptr) {
			delete[] vertices;
		}

		if (indices != nullptr) {
			delete[] indices;
		}

		if (colors != nullptr) {
			delete[] colors;
		}
		if (texture != nullptr) {
			delete texture;
		}
	}

	void ApplyModel(const glm::mat4* model) {
		this->model = *model * this->model;
	}

	void Render() override;
	void InitBuffers() override;

};
