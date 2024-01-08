#pragma once

#include "PrimitiveMesh.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char* PrimitiveMesh::vertex_shader_path = "Shaders/PrimitiveObjectShaders/vertexshader.vert";
const char* PrimitiveMesh::frag_shader_path = "Shaders/PrimitiveObjectShaders/fragmentshader.frag";

GLuint PrimitiveMesh::program_id;
GLuint PrimitiveMesh::uniform_mvp;

bool PrimitiveMesh::shaders_made = false;

PrimitiveMesh::PrimitiveMesh(GLfloat* vertices,int vertices_size
    , GLfloat* colors, int colors_size,
    GLushort* indices, int indices_size,
    PrimitveTypes type)
{
    this->type = type;

    this->vertices_size = vertices_size;
    this->colors_size = colors_size;
    this->indices_size = indices_size;

    //allocate memory for object
    this->vertices = (GLfloat*)calloc(vertices_size, sizeof(GLfloat));
    this->colors = (GLfloat*)calloc(colors_size, sizeof(GLfloat));
    this->indices = (GLushort*)calloc(indices_size, sizeof(GLushort));

    if (this->vertices == NULL || this->colors == NULL || this->indices == NULL) {
        throw std::bad_alloc();
    }

    //copy object into allocated memory
    for(int i = 0; i < vertices_size; i++)
    {
        this->vertices[i] = vertices[i];
    }
    for(int i = 0; i < colors_size; i++)
    {
        this->colors[i] = colors[i];
    }
    for(int i = 0; i < indices_size; i++)
    {
        this->indices[i] = indices[i];
    }

    if(!shaders_made)
    {
        InitShaders(vertex_shader_path, frag_shader_path, &PrimitiveMesh::program_id);
        uniform_mvp = glGetUniformLocation(program_id, "mvp");
        shaders_made = true;
    }
}


void PrimitiveMesh::Render()
{
    Object::Render();

    glm::mat4 mvp = camera->GetProjection() * camera->GetView() * model;

    // Attach to program_id
    glUseProgram(program_id);

    glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

    // Send vao
    glBindVertexArray(vao);

    glDrawElements(type, indices_size, GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(0);


}

void PrimitiveMesh::InitBuffers()
{

    GLuint position_id;
    GLuint color_id;
    GLuint vbo_vertices;
    GLuint vbo_colors;
    GLuint ibo_cube_elements;


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

    // Set up vertex attribute pointers for positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

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
        GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices_size,
        indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);


    // Stop bind to vao
    glBindVertexArray(0);
}