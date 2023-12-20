#include "PrimitiveObject.h"

void PrimitiveObject::Render()
{
	for (int mesh = 0; mesh < meshes_ammount; mesh++) {
		meshes[mesh].Render();
	}
}

void PrimitiveObject::InitBuffers()
{
	for (int mesh = 0; mesh < meshes_ammount; mesh++) {
		meshes[mesh].InitBuffers();
	}
}

void PrimitiveObject::Move(float x, float y, float z)
{
	for (int mesh = 0; mesh < meshes_ammount; mesh++) {
		this->meshes[mesh].Move(x, y, z);
	}
}

void PrimitiveObject::SetRotation(float x, float y, float z, float angle)
{
	for (int mesh = 0; mesh < meshes_ammount; mesh++) {
		meshes[mesh].SetRotation(x, y, z, angle);
	}
}

PrimitiveObject::PrimitiveObject(PrimitiveMesh* meshes,const int ammount)
{

	this->meshes = meshes;
	this->meshes_ammount = ammount;
}

PrimitiveObject::~PrimitiveObject()
{
	delete[] meshes;
}


