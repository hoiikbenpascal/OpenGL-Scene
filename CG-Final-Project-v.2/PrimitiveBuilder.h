#pragma once

#include <cmath>
#include "PrimitiveMesh.h"
#include "PrimitiveObject.h"
#include "Skybox.h"

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

	/*
	  6-----7
	 / |   /|
	2-----3 |
	|  5--|-4
	| /   |/ 
	1-----0
	*/

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
}

static PrimitiveMesh* CreateSolidRect(float height, float width, float depth, glm::vec3 color = glm::vec3(0, 0, 0)) {
	GLfloat halfWidth = width / 2.0f;
	GLfloat halfHeight = height / 2.0f;
	GLfloat halfDepth = depth / 2.0f;

	GLfloat vertices[] = {
		// Front face
		-halfWidth, -halfHeight, halfDepth,    // Vertex 0
		halfWidth, -halfHeight, halfDepth,    // Vertex 1
		halfWidth,  halfHeight, halfDepth,    // Vertex 2
		-halfWidth,  halfHeight, halfDepth,    // Vertex 3

		// Back face
		-halfWidth, -halfHeight, -halfDepth,  // Vertex 4
		halfWidth, -halfHeight, -halfDepth,  // Vertex 5
		halfWidth,  halfHeight, -halfDepth,  // Vertex 6
		-halfWidth,  halfHeight, -halfDepth   // Vertex 7
	};

	// Define colors for each vertex (you can customize this)
	GLfloat colors[] = {
		// Front face
		color[0], color[1], color[2],
		color[0], color[1], color[2],
		color[0], color[1], color[2],
		color[0], color[1], color[2],

		// Back face
		color[0], color[1], color[2],
		color[0], color[1], color[2],
		color[0], color[1], color[2],
		color[0], color[1], color[2],
	};

	// Define indices to form rectangles (front, back, left, right, top, bottom)
	GLushort indices[] = {
		0, 1, 2,  // Front face
		0, 2, 3,
		4, 5, 6,  // Back face
		4, 6, 7,
		0, 4, 7,  // Left face
		0, 7, 3,
		1, 5, 6,  // Right face
		1, 6, 2,
		3, 2, 6,  // Top face
		3, 6, 7,
		0, 1, 5,  // Bottom face
		0, 5, 4
	};

	PrimitiveMesh* mesh = new PrimitiveMesh(vertices, 24, colors, 24, indices, 36, Triangle);

	return mesh;
}
/**
* @brief this function creates a sphere object based on the input params
*
* @param radius this will be the radius of the sphere
* @param stacks the ammount of vertical stacks to be made, higher = higher quality //do note that increasing these values will impact performace
* @param slices the ammount of horizontal slices to be made, higher = higher quality //do note that increasing these values will impact performace
*/
static PrimitiveMesh* CreateSphere(float radius, uint16_t stacks, uint16_t slices, glm::vec3 color = glm::vec3(1, 1, 1)) {

	const float PI = 3.14159265358979323846;
	//calculate the size of the arrays based on the stacks and slices
	int verticesSize = (stacks + 1) * (slices + 1) * 3;
	int indicesSize = stacks * slices * 6;

	//allocate the dynamically sized arrays
	GLfloat* vertices = (GLfloat*)calloc(verticesSize, sizeof(GLfloat));
	GLushort* indices = (GLushort*)calloc(indicesSize, sizeof(GLushort));
	GLfloat* colors = (GLfloat*)calloc(verticesSize, sizeof(GLfloat));

	int vertexIndex = 0;
	int colorIndex = 0;
	int indexIndex = 0;

	// Generate the vertices and colors for the sphere
	for (int stack = 0; stack <= stacks; ++stack) {
		float stackNormalized = static_cast<float>(stack) / static_cast<float>(stacks);
		float stackAngle = stackNormalized * PI; // Latitude angle

		for (int slice = 0; slice <= slices; ++slice) {
			float sliceNormalized = static_cast<float>(slice) / static_cast<float>(slices);
			float sliceAngle = sliceNormalized * 2.0f * PI; // Longitude angle

			// Calculate vertex delta_position
			float x = radius * std::sin(stackAngle) * std::cos(sliceAngle);
			float y = radius * std::cos(stackAngle);
			float z = radius * std::sin(stackAngle) * std::sin(sliceAngle);

			// Add vertex delta_position to the array
			vertices[vertexIndex++] = x;
			vertices[vertexIndex++] = y;
			vertices[vertexIndex++] = z;

			// Add color information (you can customize this)
			colors[colorIndex++] = color[0];   // R
			colors[colorIndex++] = color[1];   // G
			colors[colorIndex++] = color[2];   // B
		}
	}

	// Generate indices for the sphere
	for (int stack = 0; stack < stacks; ++stack) {
		for (int slice = 0; slice < slices; ++slice) {
			int current = stack * (slices + 1) + slice;
			int next = current + slices + 1;

			// Triangle 1
			indices[indexIndex++] = current;
			indices[indexIndex++] = next;
			indices[indexIndex++] = current + 1;

			// Triangle 2
			indices[indexIndex++] = current + 1;
			indices[indexIndex++] = next;
			indices[indexIndex++] = next + 1;
		}
	}


	PrimitiveMesh* pointer = new PrimitiveMesh(vertices, verticesSize, colors, verticesSize, indices, indicesSize, PrimitveTypes::Triangle);
	delete[] vertices;
	delete[] indices;
	delete[] colors;
	return pointer;
}

static PrimitiveMesh* CreateCylinder(float radius, float height, uint16_t num_segments, glm::vec3 color = glm::vec3(1, 1, 1)) {
	const float PI = 3.14159265358979323846;

	// Calculate the size of the arrays based on the number of segments
	int verticesSize = (num_segments + 1) * 2 * 3; // Two rings of vertices (top and bottom)
	int indicesSize = num_segments * 6; // Each segment has two triangles

	// Allocate dynamically sized arrays
	GLfloat* vertices = (GLfloat*)calloc(verticesSize, sizeof(GLfloat));
	GLushort* indices = (GLushort*)calloc(indicesSize, sizeof(GLushort));
	GLfloat* colors = (GLfloat*)calloc(verticesSize, sizeof(GLfloat));

	int vertexIndex = 0;
	int colorIndex = 0;
	int indexIndex = 0;

	// Generate the vertices and colors for the cylinder
	for (int i = 0; i <= num_segments; ++i) {
		float angle = 2.0f * PI * i / num_segments;
		float x = radius * std::cos(angle);
		float z = radius * std::sin(angle);

		// Add top and bottom vertices
		vertices[vertexIndex++] = x;
		vertices[vertexIndex++] = height;
		vertices[vertexIndex++] = z;

		vertices[vertexIndex++] = x;
		vertices[vertexIndex++] = 0.0f;
		vertices[vertexIndex++] = z;

		colors[colorIndex++] = color[0];   // R
		colors[colorIndex++] = color[1];   // G
		colors[colorIndex++] = color[2];   // B
		colors[colorIndex++] = color[0];   // R
		colors[colorIndex++] = color[1];   // G
		colors[colorIndex++] = color[2];   // B
	}

	// Generate indices for the triangles
	for (int i = 0; i < num_segments; ++i) {
		indices[indexIndex++] = i * 2;
		indices[indexIndex++] = (i + 1) * 2;
		indices[indexIndex++] = (i + 1) * 2 + 1;

		indices[indexIndex++] = (i + 1) * 2 + 1;
		indices[indexIndex++] = i * 2 + 1;
		indices[indexIndex++] = i * 2;
	}

	PrimitiveMesh* mesh = new PrimitiveMesh(vertices, verticesSize, colors, verticesSize, indices, indicesSize, Triangle);

	return mesh;
}


static PrimitiveObject* CreatePrimitiveObject() {
	const int mesh_ammount = 2;
	PrimitiveMesh* meshes = new PrimitiveMesh[mesh_ammount]{
		*CreateLineCube(), *CreateSolidCube(3)
	};
	meshes[0].Move(0, 1.5, 0);

	return new PrimitiveObject(meshes, mesh_ammount);
}

static PrimitiveObject* CreateTree() {
	const int mesh_ammount = 2;
	PrimitiveMesh* meshes = new PrimitiveMesh[mesh_ammount]{
		*CreateCylinder(0.75f, 5, 20, { 0.2,0.13,0 }), *CreateSphere(2.75, 15, 15, { 0,255,0 })
	};
	meshes[1].Move(0, 7, 0);
	PrimitiveObject* obj = new PrimitiveObject(meshes, mesh_ammount);
	obj->Move(0, 0, 5);
	return obj;
}

