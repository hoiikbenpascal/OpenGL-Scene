#include "Object.h"
#include <glm/detail/type_mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera* Object::camera;

void Object::Render()
{

	shader->Activate();
	shader->SetStandardUniformsIfAvailable(&model, camera->GetViewPointer(), camera->GetProjectionPointer());
	shader->SetMatUniformsIfAvailable(camera->GetLightPos(), & mat);

	GLuint apply_texture_uniform = shader->GetUniform("apply_texture");

	if (apply_texture_uniform != -1) {
		glUniform1i(apply_texture_uniform, 0);
	}

	if (rotation != glm::vec4(0))
	{
		model = glm::rotate(model, glm::radians(rotation.w), glm::vec3(rotation.x, rotation.y, rotation.z));
	}

	handleAnimations();

	glBindVertexArray(vao);
}

void Object::handleAnimations()
{
	//if there are no animations to handle
	if (numberOfAnimations <= 0) {
		return;
	}

	if (AllAnimationsFinished)
	{
		return;
	}

	//if the animation isn't finished then just return
	if (!this->animations[currentAnimation].finished) {
		//apply the animation
		animations[currentAnimation].Apply(&model);
		return;
	}

	////check if the animation should be looped or not
	if (this->animations[currentAnimation].looped) {
		this->animations[currentAnimation].Restart();
		return;
	}

	//if not then go to the next animation if there is one
	if (currentAnimation + 1 < numberOfAnimations) {
		currentAnimation++;
		return;
	}

	//if all the animations need to be looped than reset the animation counter and restart all animations
	if (loopAllAnimations) {
		currentAnimation = 0;
		for (int i = 0; i < numberOfAnimations; i++) {
			animations[i].Restart();
		}
		animations[currentAnimation].Apply(&model);
		return;
	}

	AllAnimationsFinished = true;
}

void Object::setAnimations(const vector<Animation> animations, bool loopAll)
{
	numberOfAnimations = animations.size();

	this->animations = vector<Animation>();

	for (int i = 0; i < animations.size(); i++) {
		this->animations.push_back(animations[i]);
	}
	loopAllAnimations = loopAll;
}

void Object::setAnimation(const Animation animation)
{
	numberOfAnimations = 1;
	this->animations = { animation };
}

void Object::AddAnimation(Animation animation)
{
	this->animations.push_back(animation);
	numberOfAnimations++;
}
