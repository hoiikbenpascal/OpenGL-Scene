#pragma once
#include "PrimitiveMesh.h"

class Skybox : public PrimitiveMesh
{
	GLfloat* vertices;
	int vertices_size;

	GLushort* indices;
	int indices_size;

	void Render() override;
};

