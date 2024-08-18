#version 430 core

// Uniform matrices
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

in vec2 uv;

out vec2 UV;

void main()
{
    //gl_Position = vec4(position, 1.0);
    mat4 mvp = projection * view * model;
    gl_Position = mvp * vec4(position, 1.0);

    UV = uv;
}