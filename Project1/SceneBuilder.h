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

    vector<Keyframe> frames(6);

    //this is the way i used to make animations before i transfered it to a keyframe struct
    vector<glm::vec3> transform = {
        glm::vec3(0,0,0),
        glm::vec3(0,0,2.5f),
        glm::vec3(0,0,0),
        glm::vec3(0,2.5,0),
        glm::vec3(0,-2.5,0),
        glm::vec3(0,0,-2.5),
    };

    vector<glm::vec4> rotation = {
        glm::vec4(0,1,0,-90),
        glm::vec4(0,1,0,90),
        glm::vec4(0,1,0,-90),
        glm::vec4(0,1,0,90),
        glm::vec4(0,1,0,-90),
        glm::vec4(0,1,0,90)
    };

    vector<float> timestamps = {
        1,2,3,4,5,6
    };

    //which is why these for loops are needed
    for (int i = 0; i < transform.size(); i++) {
        frames[i].translate = transform[i];
    }

    for (int i = 0; i < rotation.size(); i++) {
        frames[i].rotation = rotation[i];
    }
    for (int i = 0; i < timestamps.size(); i++) {
        frames[i].time = timestamps[i];
    }

    Animation animation(frames);
    return animation;
}

static Animation CreateHopAnimation(float height = 2.5f) {
    
    vector<Keyframe> frames(2);
    
    vector<glm::vec3> transform = {
        glm::vec3(0,height,0),
        glm::vec3(0,-height,0),
    };
    vector<float> timestamps = {
        1,2
    };

    for (int i = 0; i < transform.size(); i++) {
        frames[i].translate = transform[i];
    }

    for (int i = 0; i < timestamps.size(); i++) {
        frames[i].time = timestamps[i];
    }

    Animation animation(frames);
    return animation;
}

static std::vector<Object*> CreateObjects() {

    glm::vec3 amb_diff_spec[3] = { {0,0,0}, {0,0,0}, glm::vec3(1)};


    std::vector<Object*> objects;
    objects = std::vector<Object*>{
    new LoadedObject("Objects/teapot.obj", 100, amb_diff_spec, "Textures/Yellobrk.bmp"),
    new LoadedObject("Objects/torus.obj", 1024, amb_diff_spec, "Textures/uvtemplate.bmp"),
    CreatePrimitiveObject(),
    BuildGrass(),
    CreatePerson() 
    };

    //Animation animation = CreateHopAnimation(5);
    Animation animation2 = CreateMovementAnimation();
    vector<Animation> animations = {animation2};

    //objects[0]->Move(0, 0, 0);
    //objects[0]->SetRotation(0,1,0,2);
    objects[0]->setAnimations(animations, 1);

    objects[1]->Move(3.5, 0.5f, 0);
    objects[1]->SetRotation(0, 0, 1, 2);

    objects[2]->Move(-3.5, -0.5f, 0);
    objects[2]->SetRotation(1, 0, 0, 0.05f);

    objects[3]->Move(0, -4, 0);
    objects[3]->Scale(1000, 1, 1000);

    //objects[4]->Move(0, 10, 0);

    return objects;
}
