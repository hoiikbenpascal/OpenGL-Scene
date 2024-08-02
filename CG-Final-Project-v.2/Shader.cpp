#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

GLuint Shader::GetUniform(const char* uniform_name) 
{
	GLuint uniform_location = glGetUniformLocation(programId, uniform_name);
	if (uniform_location == -1)
	{
		return -1;
	}
	return uniform_location;
}

void Shader::AddUniformsIfAvailable(const glm::mat4* model, const glm::mat4* view, const glm::mat4* projection)
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
