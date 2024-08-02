#include "Skybox.h"

void Skybox::Render()
{
	glDepthFunc(GL_LEQUAL);
	glActiveTexture(GL_TEXTURE0);
	texture->Bind();

	Object::Render();

	GLuint view_uniform = shader->GetUniform("view");
	
	//delete the last row since we don't want movement to effect the skybox
	glm::mat4 view =  glm::mat4(glm::mat3(camera->GetView()));

	// Send vao
	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);

	glDepthFunc(GL_LESS);
}
