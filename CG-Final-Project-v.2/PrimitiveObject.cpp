#include "PrimitiveObject.h"
#include <glm/gtc/matrix_transform.hpp>

const float ROTATION_SCALER = 1;

PrimitiveObject::PrimitiveObject(PrimitiveMesh* meshes, const int ammount)
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

	//rotate the mesh, some old code from before animations
	if (rotating) {
		model = glm::rotate(glm::mat4(1.0f), (rotation.w * ROTATION_SCALER), glm::vec3(rotation.x, rotation.y, rotation.z));
	}

	glm::mat4 base_mod = model;
	glm::mat4 mod = glm::inverse(model);

	//TODO: Fix this animation and movement handeling
	Object::handleAnimations();

	for (int mesh = 0; mesh < meshes_ammount; mesh++) {
		meshes[mesh].model = model * meshes[mesh].model;
		meshes[mesh].handleAnimations();
		meshes[mesh].model = mod * meshes[mesh].model;

		meshes[mesh].Render();
	}

}

void PrimitiveObject::Move(float x, float y, float z)
{
	Object::Move(x, y, z);

	for (int mesh = 0; mesh < meshes_ammount; mesh++) {
		meshes[mesh].Move(x, y, z);
	}
}

void PrimitiveObject::InitBuffers()
{
	for (int mesh = 0; mesh < meshes_ammount; mesh++) {
		this->meshes[mesh].InitBuffers();
	}

	for (int mesh = 0; mesh < meshes_ammount; mesh++) {
		this->meshes[mesh].ApplyModel(&model);
	}
	//model = glm::mat4(1.0f);
}

void PrimitiveObject::SetShaders(Shader* shader)
{
	for (int mesh = 0; mesh < meshes_ammount; mesh++) {
		this->meshes[mesh].SetShaders(shader);
	}
}

PrimitiveObject::~PrimitiveObject()
{
	delete[] meshes;
}

void PrimitiveObject::MoveOneMesh(int index, float x, float y, float z) {
	meshes[index].Move(x, y, z);
}

void PrimitiveObject::RotateOneMesh(int mesh, glm::vec3 angles, float angle, glm::vec3 pivot)
{
	meshes[mesh].Rotate(angles, angle, pivot);
}


