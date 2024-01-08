#pragma once
#include "Object.h"
#include "PrimitiveMesh.h"
#include <vector>

class PrimitiveObject :
    public Object
{
public:


    void Render() override;
    void InitBuffers() override;

    PrimitiveObject(PrimitiveMesh* meshes,const int ammount);
    PrimitiveObject(vector<PrimitiveMesh> meshes);
    ~PrimitiveObject();

    void MoveOneMesh(int index, float x,float y,float z);

private:

    PrimitiveMesh* meshes;
    int meshes_ammount;
};

