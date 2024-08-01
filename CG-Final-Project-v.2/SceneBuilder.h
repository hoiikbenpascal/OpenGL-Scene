#pragma once
#include "Object.h"
#include "PrimitiveMesh.h"
#include <vector>
#include "LoadedObject.h"
#include "PersonBuilder.h"
#include "Keyframe.h"

static PrimitiveMesh* BuildGrass() {
	// Define vertices for a quad (patch of grass)
	GLfloat vertices[] = {
		-0.5f, 0.0f, -0.5f,  // Bottom left
		0.5f, 0.0f, -0.5f,   // Bottom right
		-0.5f, 0.0f, 0.5f,   // Top left
		0.5f, 0.0f, 0.5f     // Top right
	};

	// Define indices for two triangles forming the quad
	GLushort indices[] = {
		0, 1, 2,  // Triangle 1
		1, 3, 2   // Triangle 2
	};

	// Define colors for each vertex (you can customize these)
	GLfloat colors[] = {
		0.0f, 0.8f, 0.0f,  // Bottom left
		0.0f, 0.8f, 0.0f,  // Bottom right
		0.0f, 0.8f, 0.0f,  // Top left
		0.0f, 0.8f, 0.0f   // Top right
	};

	return new PrimitiveMesh(vertices, 12, colors, 12, indices, 6, PrimitveTypes::Triangle);
}

static Animation CreateMovementAnimation() {

	float time = 1;

	glm::vec4 rotation = { 0,1,0, -90 };
	glm::vec3 move_back = { 0,0,2.5 };
	glm::vec3 move_up = { 0,2.5,0 };

	//could have made all this in the vector constructor but this made it more readable
	Keyframe move_back_and_rotate = Keyframe(move_back, rotation, time);
	Keyframe move_up_and_rotate = Keyframe(move_up, rotation, time);

	vector<Keyframe> frames = {
		move_back_and_rotate,
		move_up_and_rotate,
		move_up_and_rotate.flip(),
		move_back_and_rotate.flip()
	};
	Animation animation = Animation(frames, true);
	return animation;
}

static Animation CreateHopAnimation(bool loop = false) {

	vector<Keyframe> frames = {
		Keyframe({0,-0.5f / 0.20f, 0}, 0.20f),
		Keyframe({ 0,5.5f / 0.80f ,0 }, 0.80f),
		Keyframe({ 0,-5,0 }, 1)
	};

	Animation animation(frames, loop);
	return animation;
}

static std::vector<Object*> CreateObjects() {

	glm::vec3 amb_diff_spec[3] = { {0,0,0}, {0,0,0}, glm::vec3(1) };

	//Create the objects
	LoadedObject* teapot = new LoadedObject("Objects/teapot.obj", 100, amb_diff_spec, "Textures/Yellobrk.bmp");
	LoadedObject* torus = new LoadedObject("Objects/torus.obj", 1024, amb_diff_spec, "Textures/uvtemplate.bmp");
	PrimitiveMesh* grass = CreateSolidRect(5, 1000, 1000, { 0,255,0 });
	PrimitiveObject* tree = CreateTree();
	PrimitiveObject* person = CreatePerson();
	PrimitiveMesh* cube = CreateSolidCube();

	string primitive_shader_path = "Shaders/PrimitiveObjectShaders/";
	string loaded_object_shader_path = "Shaders/LoadedObjectShaders/";
	Shader* primitive_shader = new Shader(primitive_shader_path + "vertexshader.vert", primitive_shader_path + "fragmentshader.frag");
	Shader* loaded_object_shader = new Shader(loaded_object_shader_path + "vertexshader.vert", loaded_object_shader_path + "fragmentshader.frag");

	person->SetShaders(primitive_shader);
	teapot->SetShaders(loaded_object_shader);
	torus->SetShaders(loaded_object_shader);
	grass->SetShaders(primitive_shader);
	cube->SetShaders(primitive_shader);
	tree->SetShaders(primitive_shader);

	//Move the objects
	person->Move(0, 1.5, 0);
	teapot->Move(0, 0, 5);
	torus->Move(5, 0.5, 0);
	grass->Move(0, -2.5f, 0);

	//set animations
	//teapot->setAnimation(CreateMovementAnimation());
	//person->setAnimation(CreateHopAnimation(true));

	std::vector<Object*> objects = std::vector<Object*>{
		cube,
		//grass,
		teapot,
		//torus,
		//person,
		tree
	};

	return objects;
}

