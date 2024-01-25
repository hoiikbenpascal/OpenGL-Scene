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

    PrimitiveObject(PrimitiveMesh* meshes,const int ammount);
    PrimitiveObject(vector<PrimitiveMesh> meshes);
    ~PrimitiveObject();

    void MoveOneMesh(int index, float x,float y,float z);

    void setAnimations(const vector<Animation> animations, bool loopAll = false) override;

    void setAnimation(const Animation animation) override;

    void AddAnimation(Animation animation) override;

private:
    glm::mat4* handle_animations();
    PrimitiveMesh* meshes;
    int meshes_ammount;
    glm::vec3* movement = new glm::vec3();
};

