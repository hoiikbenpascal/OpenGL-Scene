#pragma once
#include "Object.h"
#include "PrimitiveMesh.h"
#include <vector>
#include "LoadedObject.h"
#include "PersonBuilder.h"
#include "Keyframe.h"


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

static Animation CreateMovementAnimation() {

    float time = 1;
    
    glm::vec4 rotation = { 0,1,0, -90 };
    glm::vec3 move_back = { 0,0,2.5 };
    glm::vec3 move_up = { 0,2.5,0 };

    //could have made all this in the vector constructor but this made it more readable
    Keyframe move_back_and_rotate = Keyframe(move_back, rotation, time);
    Keyframe move_up_and_rotate = Keyframe(move_up, rotation, time);
    Keyframe move_down_and_rotate = Keyframe(move_up * -1.0f, rotation, time);
    Keyframe move_forward_and_rotate = Keyframe(move_back * -1.0f, rotation, time);
    
    vector<Keyframe> frames = {
        move_back_and_rotate,
        move_up_and_rotate,
        move_up_and_rotate.flip(),
        move_forward_and_rotate
    };

    Animation animation(frames);
    return animation;
}

static Animation CreateHopAnimation(float height = 2.5f) {
    
    vector<Keyframe> frames = {
        Keyframe({ 0,5,0 }, 1),
        Keyframe({ 0,-5,0 }, 1),
        Keyframe({ 0,-5,0 }, 1)
    };

    Animation animation(frames);
    return animation;
}

static std::vector<Object*> CreateObjects() {

    glm::vec3 amb_diff_spec[3] = { {0,0,0}, {0,0,0}, glm::vec3(1)};


    std::vector<Object*> objects;
    objects = std::vector<Object*>{
    new LoadedObject("Objects/teapot.obj", 100, amb_diff_spec, "Textures/Yellobrk.bmp"),
    new LoadedObject("Objects/torus.obj", 1024, amb_diff_spec, "Textures/uvtemplate.bmp"),
    //CreatePrimitiveObject(),
    //BuildGrass(),
    CreatePerson() 
    };

    vector<Animation> animations = {
        CreateMovementAnimation()
        //CreateHopAnimation(5)
    };

    //objects[0]->Move(0, 0, 0);
    //objects[0]->SetRotation(0,1,0,2);
    objects[0]->setAnimations(animations, 1);
    //objects[0]->Move(0, 0, 0);

    objects[1]->Move(3.5, 0.5f, 0);

    objects[2]->Move(5, -0.5f, 0);

    //objects[3]->Move(0, -4, 0);
    //objects[3]->Scale(1000, 1, 1000);

    return objects;
}
