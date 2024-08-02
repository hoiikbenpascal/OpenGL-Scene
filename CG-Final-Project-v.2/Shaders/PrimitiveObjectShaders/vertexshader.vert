#version 430 core

// Uniform matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Per-vertex inputs
in vec3 position;
in vec3 color;
in vec2 uv;

// Outputs
out vec3 vColor;
out vec2 UV;

void main()
{
    //gl_Position = vec4(position, 1.0);
    mat4 mvp = projection * view * model;
    gl_Position = mvp * vec4(position, 1.0);
    vColor = color;
    UV = uv;
}
