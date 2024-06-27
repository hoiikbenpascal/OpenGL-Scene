#version 430 core

// Per-vertex inputs
in vec3 position;
in vec3 color;

uniform mat4 mvp;
in vec2 uv;

// Outputs
out vec3 vColor;
out vec2 UV;

void main()
{
    //gl_Position = vec4(position, 1.0);

    gl_Position = mvp * vec4(position, 1.0);
    vColor = color;
    UV = uv;
}
