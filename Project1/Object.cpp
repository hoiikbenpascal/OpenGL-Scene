#include "Object.h"
#include <glm/detail/type_mat4x4.hpp>

Camera* Object::camera;

void Object::handleAnimations()
{
	//if there are no animations to handle
	if (numberOfAnimations <= 0) {
		return;
	}


	//if the animation isn't finished then just return
	if (!this->animations[currentAnimation].finished) {
		//apply the animation
		animations[currentAnimation].Apply(&model);
		return;
	}

	//check if the animation should be looped or not
	if (this->animations[currentAnimation].looped) {
		this->animations[currentAnimation].Restart();
		return;
	}

	//if not then go to the next animation if there is one
	if (currentAnimation + 1 < numberOfAnimations) {
		currentAnimation++;

		//restart the new animation to make shure the time is properly tracked
		animations[currentAnimation].Restart();
		return;
	}

	//if all the animations need to be looped than reset the animation counter and restart all animations
	if (loopAllAnimations) {
		currentAnimation = 0;
		for (int i = 0; i < numberOfAnimations; i++) {
			animations[i].Restart();
		}
	}
}

void Object::Render()
{
	if(rotation != glm::vec4(0))
	{
		model = glm::rotate(model, glm::radians(rotation.w), glm::vec3(rotation.x, rotation.y, rotation.z));
	}

	handleAnimations();
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
