#pragma once
#include "Object.h"
#include "PrimitiveMesh.h"

class PrimitiveObject :
    public Object
{
public:


    void Render() override;
    void InitBuffers() override;
    void Move(float x, float y, float z) override;
    void Scale(float x, float y, float z) override;
    void SetRotation(float x, float y, float z, float angle) override;

    PrimitiveObject(PrimitiveMesh* meshes,const int ammount);
    ~PrimitiveObject();
    void MoveOneMesh(int index, float x,float y,float z);

private:
    glm::mat4* model;
    PrimitiveMesh* meshes;
    int meshes_ammount;
};

