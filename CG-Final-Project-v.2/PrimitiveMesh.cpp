#pragma once

#include "PrimitiveMesh.h"
#include "texture.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



PrimitiveMesh::PrimitiveMesh(GLfloat* vertices, int vertices_size
	, GLfloat* colors, int colors_size,
	GLushort* indices, int indices_size,
	PrimitveTypes type)
{
	this->type = type;

	this->vertices_size = vertices_size;
	this->colors_size = colors_size;
	this->indices_size = indices_size;

	//allocate memory for object
	this->vertices = (GLfloat*)calloc(vertices_size, sizeof(GLfloat));
	this->indices = (GLushort*)calloc(indices_size, sizeof(GLushort));
	this->colors = (GLfloat*)calloc(colors_size, sizeof(GLfloat));

	if (this->vertices == NULL || this->colors == NULL || this->indices == NULL) {
		throw std::bad_alloc();
	}

	//copy object into allocated memory
	for (int i = 0; i < vertices_size; i++)
	{
		this->vertices[i] = vertices[i];
	}
	for (int i = 0; i < indices_size; i++)
	{
		this->indices[i] = indices[i];
	}
	for (int i = 0; i < colors_size; i++)
	{
		this->colors[i] = colors[i];
	}

}

void PrimitiveMesh::Render()
{
	Object::Render();

	if (this->texture != nullptr) {
		glUniform1i(shader->GetUniform("apply_texture"), 1);
	}
	else
	{
		glUniform1i(shader->GetUniform("apply_texture"), 0);
	}


	// Send vao
	glBindVertexArray(vao);

	glDrawElements(type, indices_size, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);


}

void PrimitiveMesh::InitBuffers()
{

	GLuint position_id;
	GLuint color_id;
	GLuint vbo_vertices;
	GLuint vbo_colors;
	GLuint ibo_cube_elements;
	GLuint vbo_uvs;


	// vbo for vertices
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vertices_size, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vbo for colors
	glGenBuffers(1, &vbo_colors);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors) * colors_size, colors, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vbo for uvs
	glGenBuffers(1, &vbo_uvs);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2),
		uvs.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Get vertex attributes
	position_id = glGetAttribLocation(shader->programId, "position");
	color_id = glGetAttribLocation(shader->programId, "color");
	GLuint uv_id = glGetAttribLocation(shader->programId, "uv");

	// Allocate memory for vao
	glGenVertexArrays(1, &vao);

	// Bind to vao
	glBindVertexArray(vao);

	// Set up vertex attribute pointers for positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Bind vertices to vao
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Bind colors to vao
	glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
	glVertexAttribPointer(color_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(color_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (this->texture != nullptr) {
		//bind uvs to vao
		glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
		glVertexAttribPointer(uv_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(uv_id);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glGenBuffers(1, &ibo_cube_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices_size,
		indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);

	// Stop bind to vao
	glBindVertexArray(0);
}