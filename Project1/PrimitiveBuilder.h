#pragma once

#include "PrimitiveObject.h"

static PrimitiveObject* CreateCube()
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

    GLushort elements[] = {
        0,1,1,2,2,3,3,0,  // front
        0,4,1,5,3,7,2,6,  // front to back
        4,5,5,6,6,7,7,4   //back
    };

	return new PrimitiveObject(vertices, std::size(vertices), colors, std::size(colors), elements, std::size(elements));
}
