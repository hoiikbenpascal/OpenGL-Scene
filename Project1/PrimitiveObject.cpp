#include "PrimitiveObject.h"
#include <glm/gtc/matrix_transform.hpp>

const float ROTATION_SCALER = 1;

glm::mat4* PrimitiveObject::handle_animations() {

	glm::mat4* animated_model = new glm::mat4(model);
	if (currentAnimation < numberOfAnimations) {
		animations[currentAnimation].Apply(animated_model);

		//loop or increment animations
		if (animations[currentAnimation].finished) {
			animations[currentAnimation].Restart();
			if (!animations[currentAnimation].looped) {
			currentAnimation++;
			}
		}

	}
	//loop all animations
	else if (loopAllAnimations) {
		for (Animation animation : animations) {
			animation.Restart();
		}
		currentAnimation = 0;
	}
	return animated_model;
}


PrimitiveObject::PrimitiveObject(PrimitiveMesh* meshes,const int ammount)
{
	this->model = glm::mat4(1.0f);
	this->meshes = meshes;
	this->meshes_ammount = ammount;

}

PrimitiveObject::PrimitiveObject(std::vector<PrimitiveMesh> meshes)
{
	this->model = glm::mat4(1.0f);
	this->meshes = meshes.data();
	this->meshes_ammount = meshes.size();

}



void PrimitiveObject::Render()
{


	//rotate the mesh some old code from before animations
	if (rotating) {
		model = glm::rotate(glm::mat4(1.0f), (rotation.w * ROTATION_SCALER), glm::vec3(rotation.x, rotation.y, rotation.z));
	}

	glm::mat4* animated_model = handle_animations();

	for (int mesh = 0; mesh < meshes_ammount; mesh++) {
		meshes[mesh].ApplyModel(animated_model);
		meshes[mesh].ApplyModel(&model);
		meshes[mesh].Render();
	}
	
	delete animated_model;
}

void PrimitiveObject::Move(float x, float y, float z)
{
	Object::Move(x,y,z);
	*movement += glm::vec3(x, y, z);
}

void PrimitiveObject::InitBuffers()
{
	for (int mesh = 0; mesh < meshes_ammount; mesh++) {
		meshes[mesh].InitBuffers();
	}

	for (int mesh = 0; mesh < meshes_ammount; mesh++) {
		this->meshes[mesh].ApplyModel(&model);
	}
	model = glm::mat4(1.0f);
}

PrimitiveObject::~PrimitiveObject()
{
	delete[] meshes;
	delete movement;
}

void PrimitiveObject::MoveOneMesh(int index, float x,float y,float z) {
	meshes[index].Move(x, y, z);
}

void PrimitiveObject::setAnimations(const vector<Animation> animations, bool loopAll)
{
	for (Animation animation : animations) {
		animation.movement = movement;
	}

	Object::setAnimations(animations, loopAll);
}

void PrimitiveObject::setAnimation(Animation animation)
{
	animation.movement = movement;
	Object::setAnimation(animation);
}

void PrimitiveObject::AddAnimation(Animation animation)
{
	animation.movement = movement;
	Object::AddAnimation(animation);
}


