#include "LoadedObject.h"
#include "texture.h"
#include "objloader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


const char* LoadedObject::vertex_shader_path = "Shaders/LoadedObjectShaders/vertexshader.vert";
const char* LoadedObject::frag_shader_path = "Shaders/LoadedObjectShaders/fragmentshader.frag";

bool LoadedObject::shaders_made = false;
GLuint LoadedObject::program_id;
GLuint LoadedObject::uniform_material_ambient;
GLuint LoadedObject::uniform_material_diffuse;
GLuint LoadedObject::uniform_material_power;
GLuint LoadedObject::uniform_specular;
GLuint LoadedObject::uniform_mv;
GLuint LoadedObject::uniform_proj;
GLuint LoadedObject::uniform_light_pos;
GLuint LoadedObject::uniform_apply_texture;


LoadedObject::LoadedObject(const char object_path[], float power, glm::vec3 amb_diff_spec[],
	const char texture_path[])
{

	//check if the shaders have been intitialised, if they haven't been then initialise them
	if (!shaders_made)
	{
		InitShaders(vertex_shader_path, frag_shader_path, &LoadedObject::program_id);
		shaders_made = true;
	}

	//load the object
	bool res = loadOBJ(object_path, vertices, uvs, normals);
	if (texture_path != nullptr && res)
	{
		texture_id = loadBMP(texture_path);
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
	GLuint position_id;
	GLuint vbo_vertices;
	GLuint vbo_normals;
	GLuint vbo_uvs;

	//bind vbo's
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER,
		vertices.size() * sizeof(glm::vec3), vertices.data(),
		GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vbo for normals
	glGenBuffers(1, &vbo_normals);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
	glBufferData(GL_ARRAY_BUFFER,
		normals.size() * sizeof(glm::vec3),
		normals.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// vbo for uvs
	glGenBuffers(1, &vbo_uvs);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2),
		uvs.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Get vertex attributes
	position_id = glGetAttribLocation(program_id, "position");
	GLuint normal_id = glGetAttribLocation(program_id, "normal");
	GLuint uv_id = glGetAttribLocation(program_id, "uv");

	// Allocate memory for vao
	glGenVertexArrays(1, &this->vao);

	// Bind to vao
	glBindVertexArray(this->vao);

	// Bind vertices to vao
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(position_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
	glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(normal_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
	glVertexAttribPointer(uv_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(uv_id);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//stop bind to vao
	glBindVertexArray(0);

	glUseProgram(program_id);

	//fill object's uniforms
	uniform_mv = glGetUniformLocation(program_id, "mv");
	uniform_proj = glGetUniformLocation(program_id, "projection");

	uniform_material_ambient = glGetUniformLocation(program_id,
		"mat_ambient");
	uniform_material_diffuse = glGetUniformLocation(program_id,
		"mat_diffuse");
	uniform_specular = glGetUniformLocation(
		program_id, "mat_specular");
	uniform_material_power = glGetUniformLocation(
		program_id, "mat_power");
	uniform_apply_texture = glGetUniformLocation(
		program_id, "apply_texture");
	uniform_light_pos = glGetUniformLocation(program_id, "light_pos");

}

void LoadedObject::Render()
{
	Object::Render();

	glm::mat4 view = camera->GetView();

	// Attach to program_id
	glUseProgram(program_id);

	glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(view * model));

	if (apply_texture)
	{
		glUniform1i(uniform_apply_texture, 1);
		glBindTexture(GL_TEXTURE_2D, texture_id);
	}

	// Fill uniform vars
	glUniformMatrix4fv(uniform_proj, 1, GL_FALSE, glm::value_ptr(camera->GetProjection()));
	glUniform3fv(uniform_material_ambient, 1, glm::value_ptr(amb_diff_spec[0]));
	glUniform3fv(uniform_material_diffuse, 1, glm::value_ptr(amb_diff_spec[1]));
	glUniform3fv(uniform_specular, 1, glm::value_ptr(amb_diff_spec[2]));
	//glUniform3fv(uniform_light_pos, 1, glm::value_ptr(camera->GetLightPos()));
	glUniform1f(uniform_material_power, power);
	glUniform1f(uniform_apply_texture, apply_texture);

	// Send mv
	glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(view * model));

	// Send vao
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);

}



