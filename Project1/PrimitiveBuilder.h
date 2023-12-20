#pragma once

#include "PrimitiveMesh.h"
#include "PrimitiveObject.h"

static PrimitiveMesh* CreateLineCube()
{
    GLfloat vertices[] = {
        // front
        -1.0, -1.0, 1.0,
        1.0, -1.0, 1.0,
        1.0, 1.0, 1.0,
        -1.0, 1.0, 1.0,
        // back
        -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0,
        1.0, 1.0, -1.0,
        -1.0, 1.0, -1.0
    };

    GLfloat colors[] = {
        // front colors
        1.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 1.0, 1.0,
        // back colors
        0.0, 1.0, 1.0,
        1.0, 0.0, 1.0,
        1.0, 0.0, 0.0,
        1.0, 1.0, 0.0
    };

    GLushort indices[] = {
        0,1,1,2,2,3,3,0,  // front
        0,4,1,5,3,7,2,6,  // front to back
        4,5,5,6,6,7,7,4   //back
    };

	return new PrimitiveMesh(vertices, std::size(vertices), colors, std::size(colors), indices, std::size(indices));
}

static PrimitiveMesh* CreateSolidCube(float sideLength = 2) {

    float halfLength = sideLength * 0.5;

    GLfloat vertices[] = {
        -halfLength, -halfLength, -halfLength,  // Vertex 0
        halfLength, -halfLength, -halfLength,  // Vertex 1
        halfLength,  halfLength, -halfLength,  // Vertex 2
        -halfLength,  halfLength, -halfLength,  // Vertex 3
        -halfLength, -halfLength,  halfLength,  // Vertex 4
        halfLength, -halfLength,  halfLength,  // Vertex 5
        halfLength,  halfLength,  halfLength,  // Vertex 6
        -halfLength,  halfLength,  halfLength   // Vertex 7
    };

    GLushort indices[] = {
        0, 1, 2,  2, 3, 0,  // Front face
        4, 5, 6,  6, 7, 4,  // Back face
        1, 5, 6,  6, 2, 1,  // Right face
        0, 4, 7,  7, 3, 0,  // Left face
        0, 1, 5,  5, 4, 0,  // Bottom face
        2, 3, 7,  7, 6, 2   // Top face
    };

    // Color data for a solid red cube
    GLfloat colors[] = {
        // front colors
        1.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 1.0, 1.0,

        // back colors
        0.0, 1.0, 1.0,
        1.0, 0.0, 1.0,
        1.0, 0.0, 0.0,
        1.0, 1.0, 0.0
    };

    return new PrimitiveMesh(vertices, 24, colors, 24, indices, 36, Triangle);
    //return new PrimitiveMesh(Solidvertices, std::size(Solidvertices), Solidcolors, std::size(Solidcolors), Solidelements, std::size(Solidelements), PrimitveTypes::Triangle);
}

static PrimitiveObject* CreatePrimitiveObject() {
    const int mesh_ammount = 2;
    PrimitiveMesh* meshes = new PrimitiveMesh[mesh_ammount]{
        *CreateLineCube(), *CreateSolidCube(3)
    };
    meshes[0].Move(0, 1.5, 0);
    //meshes[0] = *CreateLineCube();
    //meshes[1] = *CreateSolidCube(3);

    return new PrimitiveObject(meshes, mesh_ammount);
}
