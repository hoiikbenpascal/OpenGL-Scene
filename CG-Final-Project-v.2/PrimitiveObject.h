#pragma once
#include "Object.h"
#include "PrimitiveMesh.h"
#include <vector>

class PrimitiveObject :
	public Object
{
public:


	void Render() override;
	void Move(float x, float y, float z) override;
	void InitBuffers() override;
	void SetShaders(Shader* shader) override;

	PrimitiveObject(PrimitiveMesh* meshes, const int ammount);
	PrimitiveObject(vector<PrimitiveMesh> meshes);
	~PrimitiveObject();

	void MoveOneMesh(int index, float x, float y, float z);

private:
	//glm::mat4* handle_animations();
	PrimitiveMesh* meshes;
	int meshes_ammount;
};

