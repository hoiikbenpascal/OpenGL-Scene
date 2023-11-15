#pragma once

#include "PrimitiveObject.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char* PrimitiveObject::vertex_shader_path = "Shaders/PrimitiveObjectShaders/vertexshader.vert";
const char* PrimitiveObject::frag_shader_path = "Shaders/PrimitiveObjectShaders/fragmentshader.frag";

GLuint PrimitiveObject::program_id;
GLuint PrimitiveObject::uniform_mvp;

bool PrimitiveObject::shaders_made = false;

PrimitiveObject::PrimitiveObject(GLfloat vertices[],int vertices_size , GLfloat colors[], int colors_size, GLushort elements[], int elements_size)
{
    this->vertices_size = vertices_size;
    this->colors_size = colors_size;
    this->elements_size = elements_size;

    this->vertices = (GLfloat*)calloc(vertices_size, sizeof(GLfloat));
    this->colors = (GLfloat*)calloc(colors_size, sizeof(GLfloat));
    this->elements = (GLushort*)calloc(elements_size, sizeof(GLushort));

    for(int i = 0; i < vertices_size; i++)
    {
        this->vertices[i] = vertices[i];
    }
    for(int i = 0; i < colors_size; i++)
    {
        this->colors[i] = colors[i];
    }
    for(int i = 0; i < elements_size; i++)
    {
        this->elements[i] = elements[i];
    }

    if(!shaders_made)
    {
        InitShaders(vertex_shader_path, frag_shader_path, &PrimitiveObject::program_id);
        shaders_made = true;
    }
}


void PrimitiveObject::Render()
{
    if (rotating) {
        model = glm::rotate(model, rotation.w, glm::vec3(rotation.x, rotation.y, rotation.z));
    }
    glm::mat4 mvp = camera->GetProjection() * camera->GetView() * model;

    // Attach to program_id
    glUseProgram(program_id);

    // Send vao
    glBindVertexArray(vao);

    glDrawElements(GL_LINES, elements_size, GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(0);

    glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

}

void PrimitiveObject::InitBuffers()
{

    GLuint position_id;
    GLuint color_id;
    GLuint vbo_vertices;
    GLuint vbo_colors;
    GLuint ibo_cube_elements;

    uniform_mvp = glGetUniformLocation(program_id, "mvp");

    // vbo for vertices
    glGenBuffers(1, &vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vertices_size, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vbo for colors
    glGenBuffers(1, &vbo_colors);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors) * colors_size, colors, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Get vertex attributes
    position_id = glGetAttribLocation(program_id, "position");
    color_id = glGetAttribLocation(program_id, "color");


    // Allocate memory for vao
    glGenVertexArrays(1, &vao);

    // Bind to vao
    glBindVertexArray(vao);

    // Bind vertices to vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind colors to vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glVertexAttribPointer(color_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(color_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &ibo_cube_elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,  elements_size * sizeof(elements),
        elements, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);

    // Stop bind to vao
    glBindVertexArray(0);
}

void PrimitiveObject::Move(float x, float y, float z)
{
    model = glm::translate(model, glm::vec3(x, y, z));
}


