#include "LoadedObject.h"
#include "texture.h"
#include "objloader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


LoadedObject::LoadedObject(const char object_path[], const Material* mat,
	const char texture_path[])
{

	//load the object
	bool res = loadOBJ(object_path, vertices, uvs, normals);
	
	if (mat != nullptr) {
		this->mat = *mat;
	}

	if (texture_path != nullptr) {
		this->texture = Texture();
		this->texture.Load(texture_path);
		apply_texture = true;
	}

	//set the amb diff and spec
	if (amb_diff_spec != nullptr)
	{
		for (int i = 0; i < amb_diff_spec_size; i++)
		{
			this->amb_diff_spec[i] = amb_diff_spec[i];
		}
	}

	this->rotation = glm::vec4(0);

	this->power = power;

}

void LoadedObject::InitBuffers()
{
	GLuint vbo_vertices;
	GLuint vbo_normals;
	GLuint vbo_uvs;

	// Allocate memory for vao
	glGenVertexArrays(1, &this->vao);

	//bind vbo's
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, 
		vertices.size() * sizeof(glm::vec3), vertices.data(),
		GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vbo_normals);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
	glBufferData(GL_ARRAY_BUFFER,
		normals.size() * sizeof(glm::vec3), normals.data(),
		GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vbo for uvs
	glGenBuffers(1, &vbo_uvs);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2),
		uvs.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Get vertex attributes
	GLuint position_id = glGetAttribLocation(shader->programId, "position");
	GLuint normal_id = glGetAttribLocation(shader->programId, "normal");
	GLuint uv_id = glGetAttribLocation(shader->programId, "uv");

	// Bind to vao
	glBindVertexArray(this->vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Bind vertices to vao
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//bind normals
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
	glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(normal_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//bind uvs
	glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
	glVertexAttribPointer(uv_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(uv_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//stop bind to vao
	glBindVertexArray(0);
}

void LoadedObject::Render()
{
	Object::Render();

	if (apply_texture) {
		texture.Activate();
		glUniform1i(shader->GetUniform("apply_texture"), 1);
	}
	else
	{
		glUniform1i(shader->GetUniform("apply_texture"), 0);
	}

	// Send vao

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);

}



