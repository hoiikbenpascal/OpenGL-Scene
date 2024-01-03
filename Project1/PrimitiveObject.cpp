#include "PrimitiveObject.h"
#include <glm/gtc/matrix_transform.hpp>

const float ROTATION_SCALER = 1;

PrimitiveObject::PrimitiveObject(PrimitiveMesh* meshes,const int ammount)
{
	this->model = new glm::mat4(1.0f);
	this->meshes = meshes;
	this->meshes_ammount = ammount;

}

PrimitiveObject::PrimitiveObject(std::vector<PrimitiveMesh> meshes)
{
	this->model = new glm::mat4(1.0f);
	this->meshes = meshes.data();
	this->meshes_ammount = meshes.size();

}



void PrimitiveObject::Render()
{
	if (rotating) {
		*model = glm::rotate(glm::mat4(1.0f), (rotation.w * ROTATION_SCALER), glm::vec3(rotation.x, rotation.y, rotation.z));
	}

	for (int mesh = 0; mesh < meshes_ammount; mesh++) {
		meshes[mesh].ApplyModel(model);
		meshes[mesh].Render();
	}
	

}

void PrimitiveObject::InitBuffers()
{
	for (int mesh = 0; mesh < meshes_ammount; mesh++) {
		meshes[mesh].InitBuffers();
	}

	for (int mesh = 0; mesh < meshes_ammount; mesh++) {
		this->meshes[mesh].ApplyModel(model);
	}
	*model = glm::mat4(1.0f);
}

void PrimitiveObject::Move(float x, float y, float z)
{
	*model = glm::translate(*model, glm::vec3(x, y, z));
}

void PrimitiveObject::Scale(float x, float y, float z)
{
	*model = glm::scale(*model, glm::vec3(x, y, z));
}

void PrimitiveObject::SetRotation(float x, float y, float z, float angle)
{
//	for (int mesh = 0; mesh < meshes_ammount; mesh++) {
//		meshes[mesh].SetRotation(x, y, z, angle);
//	}
	if (x && y && z && angle == 0) {
		rotating = false;
		return;
	}

	rotating = true;
	this->rotation = glm::vec4(x, y, z, angle);
}

PrimitiveObject::~PrimitiveObject()
{
	delete model;
	delete[] meshes;
}

void PrimitiveObject::MoveOneMesh(int index, float x,float y,float z) {
	meshes[index].Move(x, y, z);
}


