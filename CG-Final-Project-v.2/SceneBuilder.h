#pragma once
#include "Object.h"
#include "PrimitiveMesh.h"
#include <vector>
#include "LoadedObject.h"
#include "PersonBuilder.h"
#include "Keyframe.h"
#include "Skybox.h"

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
	LoadedObject* huis = new LoadedObject("Objects/huis.obj", 1, amb_diff_spec);
	//LoadedObject* teapot = new LoadedObject("Objects/teapot.obj", 100, amb_diff_spec, "Textures/Yellobrk.bmp");
	//LoadedObject* torus = new LoadedObject("Objects/torus.obj", 1024, amb_diff_spec, "Textures/uvtemplate.bmp");
	PrimitiveObject* tree = CreateTree();
	PrimitiveObject* person = CreatePerson();
	Skybox* skybox = new Skybox(); //(Skybox*)CreateSolidCube();

	string primitive_shader_path = "Shaders/PrimitiveObjectShaders/";
	string loaded_object_shader_path = "Shaders/LoadedObjectShaders/";
	string cube_map_shader_path = "Shaders/CubeMapShaders/";
	string skybox_shader_path = "Shaders/Skyboxshaders/";

	//Shader* primitive_shader = new Shader(primitive_shader_path + "vertexshader.vert", primitive_shader_path + "fragmentshader.frag");
	Shader* loaded_object_shader = new Shader(loaded_object_shader_path + "vertexshader.vert", loaded_object_shader_path + "fragmentshader.frag");
	Shader* cube_map_shader = new Shader(cube_map_shader_path + "vertexshader.vert", cube_map_shader_path + "fragmentshader.frag");
	Shader* skybox_shader = new Shader(skybox_shader_path + "vertexshader.vert", skybox_shader_path + "fragmentshader.frag");

	huis->SetShaders(loaded_object_shader);

	//person->SetShaders(primitive_shader);
	//teapot->SetShaders(loaded_object_shader);
	//torus->SetShaders(loaded_object_shader);
	//tree->SetShaders(primitive_shader);

	skybox->SetShaders(skybox_shader);

	////Move the objects
	//person->Move(0, 1.5, 0);
	//teapot->Move(0, 0, 5);
	//torus->Move(5, 0.5, 0);

	vector<string> cube_map_file_locations =
	{
	"Textures/Skybox/right.bmp",
	"Textures/Skybox/left.bmp",
	"Textures/Skybox/top.bmp",
	"Textures/Skybox/bottom.bmp",
	"Textures/Skybox/front.bmp",
	"Textures/Skybox/back.bmp"
	};

	skybox->texture = new Texture(GL_TEXTURE_CUBE_MAP);
	skybox->texture->LoadCubeMap(cube_map_file_locations);
	

	//set animations
	//teapot->setAnimation(CreateMovementAnimation());
	//person->setAnimation(CreateHopAnimation(true));

	std::vector<Object*> objects = std::vector<Object*>{
		skybox,
		huis
		//teapot,
		//torus,
		//person,
		//tree
	};

	return objects;
}

