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

	vector<glm::vec2> uvs;
	int uv_scale = 1;
	bool apply_texture = false;

	PrimitveTypes type;

	GLuint texture_id;

	static const char* vertex_shader_path;
	static const char* frag_shader_path;
	static GLuint uniform_mvp;
	static GLuint program_id;
	static GLuint uniform_apply_texture;
	static GLuint uniform_uv_scale;
	static bool shaders_made;

public:

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

	void ApplyTexture(const char* texture_path, const vector<glm::vec2>* uvs, int uv_scale = 1);

	void ApplyModel(const glm::mat4* model) {
		this->model = *model * this->model;
	}

	void Render() override;
	void InitBuffers() override;

};
