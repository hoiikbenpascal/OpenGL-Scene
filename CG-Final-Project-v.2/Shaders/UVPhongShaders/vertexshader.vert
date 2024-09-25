#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

// Uniform matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Per-vertex inputs
in vec2 uv;

out VS_OUT
{
   vec3 normal;
   vec3 view;
   vec3 frag_pos;
} vs_out;

out vec2 UV;

void main()
{

    vs_out.frag_pos = vec3(model * vec4(position, 1.0));

    // Calculate normal in view-space
    vs_out.normal = mat3(transpose(inverse(model))) * normal;

    // Calculate view vector;
    vs_out.view =  -(view * model * vec4(position, 1.0)).xyz;

    // Calculate the clip-space position of each vertex
    gl_Position = projection * view * vec4(vs_out.frag_pos, 1.0);

    UV = uv;
}