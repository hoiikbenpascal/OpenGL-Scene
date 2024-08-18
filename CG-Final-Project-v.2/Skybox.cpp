#include "Skybox.h"
#include <glm/gtc/type_ptr.hpp>

Skybox::Skybox(std::vector<string> paths)
{
	float halfLength = 0.5;

	/*
	  6-----7
	 / |   /|
	2-----3 |
	|  5--|-4
	| /   |/
	1-----0
	*/

	this->vertices_size = 24;
	this->indices_size = 36;

	//allocate memory for object
	this->vertices = (GLfloat*)calloc(vertices_size, sizeof(GLfloat));
	this->indices = (GLushort*)calloc(indices_size, sizeof(GLushort));

	GLfloat vertices[] = {
		-halfLength, -halfLength, -halfLength,  // Vertex 0
		halfLength, -halfLength, -halfLength,  // Vertex 1
		halfLength,  halfLength, -halfLength,  // Vertex 2
		-halfLength,  halfLength, -halfLength,  // Vertex 3
		-halfLength, -halfLength,  halfLength,  // Vertex 4
		halfLength, -halfLength,  halfLength,  // Vertex 5
		halfLength,  halfLength,  halfLength,  // Vertex 6
		-halfLength,  halfLength,  halfLength   // Vertex 7
	};
	GLushort indices[] = {
		0, 1, 2,  2, 3, 0,  // Front face
		4, 5, 6,  6, 7, 4,  // Back face
		1, 5, 6,  6, 2, 1,  // Right face
		0, 4, 7,  7, 3, 0,  // Left face
		0, 1, 5,  5, 4, 0,  // Bottom face
		2, 3, 7,  7, 6, 2   // Top face
	};

	//copy object into allocated memory
	for (int i = 0; i < vertices_size; i++)
	{
		this->vertices[i] = vertices[i];
	}
	for (int i = 0; i < indices_size; i++)
	{
		this->indices[i] = indices[i];
	}

	type = PrimitveTypes::Triangle;

	vector<string> cube_map_file_locations =
	{
	"Textures/Skybox/right.bmp",
	"Textures/Skybox/left.bmp",
	"Textures/Skybox/top.bmp",
	"Textures/Skybox/bottom.bmp",
	"Textures/Skybox/front.bmp",
	"Textures/Skybox/back.bmp"
	};

	texture = new Texture(GL_TEXTURE_CUBE_MAP);
	texture->LoadCubeMap(cube_map_file_locations);
}

void Skybox::Render()
{
	glDepthFunc(GL_LEQUAL);

	Object::Render();

	GLuint view_uniform = shader->GetUniform("view");
	
	//delete the last row since we don't want movement to effect the skybox
	glm::mat4 view =  glm::mat4(glm::mat3(camera->GetView()));

	glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(view));

	// Send vao
	glBindVertexArray(vao);

	//texture->Activate();

	glDrawElements(type, indices_size, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);

	glDepthFunc(GL_LESS);
}
