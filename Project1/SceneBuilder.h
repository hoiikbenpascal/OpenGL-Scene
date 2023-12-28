#pragma once
#include "Object.h"
#include "PrimitiveMesh.h"
#include <vector>
#include "LoadedObject.h"
#include "PrimitiveBuilder.h"


static PrimitiveMesh* BuildGrass() {
    // Define vertices for a quad (patch of grass)
    GLfloat vertices[] = {
        -0.5f, 0.0f, -0.5f,  // Bottom left
        0.5f, 0.0f, -0.5f,   // Bottom right
        -0.5f, 0.0f, 0.5f,   // Top left
        0.5f, 0.0f, 0.5f     // Top right
    };

    // Define indices for two triangles forming the quad
    GLushort indices[] = {
        0, 1, 2,  // Triangle 1
        1, 3, 2   // Triangle 2
    };

    // Define colors for each vertex (you can customize these)
    GLfloat colors[] = {
        0.0f, 0.8f, 0.0f,  // Bottom left
        0.0f, 0.8f, 0.0f,  // Bottom right
        0.0f, 0.8f, 0.0f,  // Top left
        0.0f, 0.8f, 0.0f   // Top right
    };

    return new PrimitiveMesh(vertices, 12, colors, 12, indices, 6, PrimitveTypes::Triangle);
}



static std::vector<Object*> CreateObjects() {

    glm::vec3 amb_diff_spec[3] = { {0,0,0}, {0,0,0}, glm::vec3(1)};

    std::vector<Object*> objects = std::vector<Object*>{
    new LoadedObject("Objects/teapot.obj", 100, amb_diff_spec, "Textures/Yellobrk.bmp"),
    new LoadedObject("Objects/torus.obj", 1024, amb_diff_spec, "Textures/uvtemplate.bmp"),
    CreatePrimitiveObject(),
    BuildGrass()
    };



    //objects[0].Move(0, 0, 0);
    objects[0]->SetRotation(0,1,0,2);

    objects[1]->Move(3.5, 0.5f, 0);
    objects[1]->SetRotation(0, 0, 1, 2);

    objects[2]->Move(-3.5, -0.5f, 0);
    objects[2]->SetRotation(1, 0, 0, 0.05f);

    objects[3]->Move(0, -4, 0);
    objects[3]->Scale(1000, 1, 1000);

    return objects;
}
