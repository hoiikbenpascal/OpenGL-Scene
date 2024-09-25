#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(std::string vertex_path, std::string fragment_path)
{
	char* vertexshader = glsl::readFile(vertex_path.c_str());
	char* fragshader = glsl::readFile(fragment_path.c_str());

	GLuint vsh_id = glsl::makeVertexShader(vertexshader);
	GLuint fsh_id = glsl::makeFragmentShader(fragshader);
	programId = glsl::makeShaderProgram(vsh_id, fsh_id);
}

Shader::Shader(std::string folder_path) {
	char* vertexshader = glsl::readFile((folder_path + "vertexshader.vert").c_str());
	char* fragshader = glsl::readFile((folder_path + "fragmentshader.frag").c_str());

	GLuint vsh_id = glsl::makeVertexShader(vertexshader);
	GLuint fsh_id = glsl::makeFragmentShader(fragshader);
	programId = glsl::makeShaderProgram(vsh_id, fsh_id);
}

GLuint Shader::GetUniform(const char* uniform_name)
{
	GLuint uniform_location = glGetUniformLocation(programId, uniform_name);
	if (uniform_location == -1)
	{
		return -1;
	}
	return uniform_location;
}

void Shader::SetStandardUniformsIfAvailable(const glm::mat4* model, const glm::mat4* view, const glm::mat4* projection)
{
	GLuint model_uniform = GetUniform("model");
	GLuint view_uniform = GetUniform("view");
	GLuint projection_uniform = GetUniform("projection");

	if (model_uniform != -1)
	{
		glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(*model));
	}

	if (view_uniform != -1)
	{
		glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(*view));
	}

	if (projection_uniform != -1)
	{
		glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(*projection));
	}
}

void Shader::SetMatUniformsIfAvailable(const glm::vec3 light_pos, const Material* mat)
{
	GLuint light_uniform = GetUniform("light_pos");

	if (light_uniform != -1) {
		glUniform3fv(light_uniform, 0, glm::value_ptr(light_pos));
	}

	if (mat == nullptr) {
		return;
	}

	GLuint mat_ambient = GetUniform("mat_ambient");
	GLuint mat_diffuse = GetUniform("mat_diffuse");
	GLuint mat_specular = GetUniform("mat_specular");
	GLuint mat_power = GetUniform("mat_power");

	if (mat_ambient != -1) {
		glUniform3fv(mat_ambient, 1, glm::value_ptr(mat->ambient));
	}

	if (mat_diffuse != -1) {
		glUniform3fv(mat_diffuse, 1, glm::value_ptr(mat->diffuse));
	}

	if (mat_specular != -1) {
		glUniform3fv(mat_specular, 1, glm::value_ptr(mat->specular));
	}


	if (mat_power != -1) {
		glUniform1f(mat_power, mat->power);
	}
}

void Shader::Activate()
{
	glUseProgram(programId);
}
