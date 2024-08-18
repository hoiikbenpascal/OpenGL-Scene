#version 430 core

// Uniform matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Per-vertex inputs
in vec3 position;

out vec3 texCoords;

void main()
{
    vec4 pos = projection * view * vec4(position, 1.0f);
    gl_Position =  projection * view * model * vec4(position, 1.0);
    // We want to flip the z axis due to the different coordinate systems (left hand vs right hand)
    texCoords = vec3(position.x, position.y, -position.z);
}