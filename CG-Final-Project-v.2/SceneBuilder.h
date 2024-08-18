#pragma once
#include "Object.h"
#include "PrimitiveMesh.h"
#include <vector>
#include "LoadedObject.h"
#include "PersonBuilder.h"
#include "Keyframe.h"
#include "Skybox.h"

static Shader* primitive_shader;
static Shader* phong_shaders;
static Shader* skybox_shader;
static Shader* cubemap_shader;

static Animation CreateMovementAnimation() {

	float time = 1;

	glm::vec4 rotation = { 0,1,0, -90 };
	glm::vec3 move_back = { 0,0,2.5 };
	glm::vec3 move_up = { 0,2.5,0 };

	//could have made all this in the vector constructor but this made it more readable
	Keyframe move_back_and_rotate = Keyframe(move_back, rotation, time);
	Keyframe move_up_and_rotate = Keyframe(move_up, rotation, time);
	Keyframe rotateAroundPoint = Keyframe({ 0,1,0,180 }, 2, { 0,0,-1 });
	Keyframe rotateAroundPointFlip = Keyframe({ 0,1,0,-180 }, 2, { 0,0,1 });

	vector<Keyframe> frames = {
		move_back_and_rotate,
		move_up_and_rotate,
		rotateAroundPoint,
		rotateAroundPointFlip,
		move_up_and_rotate.flip(),
		move_back_and_rotate.flip()
	};
	Animation animation = Animation(frames, true);
	return animation;
}

static void InitShaders() {
	primitive_shader = new Shader("Shaders/PrimitiveObjectShaders/");
	phong_shaders = new Shader("Shaders/UVPhongShaders/");
	skybox_shader = new Shader("Shaders/Skyboxshaders/");
	cubemap_shader = new Shader("Shaders/CubeMapShaders/");
}

static std::vector<Object*> CreateBaseObjects() {
	Skybox* skybox = new Skybox({
	"Textures/Skybox/right.bmp",
	"Textures/Skybox/left.bmp",
	"Textures/Skybox/top.bmp",
	"Textures/Skybox/bottom.bmp",
	"Textures/Skybox/front.bmp",
	"Textures/Skybox/back.bmp" });
	PrimitiveMesh* floor = CreatePlane(1000, 1000, "Textures/grass-top.bmp", 100, 100);
	PrimitiveMesh* road = CreatePlane(10, 1000, "Textures/road_bmp.bmp", 1, 100);
	road->Move(0, 0.1, 0);

	skybox->SetShaders(skybox_shader);
	floor->SetShaders(primitive_shader);
	road->SetShaders(primitive_shader);
	std::vector<Object*> objects = vector<Object*>{skybox, floor, road};
	std::vector<Object*> trees_right = CreateTreeRow(100, 0, 7.5, primitive_shader, {7.5,0,-500});
	std::vector<Object*> trees_left = CreateTreeRow(100, 0, 7.5, primitive_shader, {-7.5,0,-500});

	for (int i = 0; i < trees_left.size(); i++) {
		objects.push_back(trees_left[i]);
		objects.push_back(trees_right[i]);
	}

	objects.push_back(CreateHouse(primitive_shader, cubemap_shader, {10,0.2, 10}));
	//objects.push_back(CreatePerson(primitive_shader));
	//objects[objects.size() - 1]->Move(0,1,0);
	return objects;
}

static std::vector<Object*> CreateObjects() {
	InitShaders();

	Material* shiny_mat = new Material(glm::vec3(0.4), glm::vec3(1), glm::vec3(1.2), 10);

	//create the objects
	LoadedObject* teapot = new LoadedObject("Objects/teapot.obj", shiny_mat, "Textures/Yellobrk.bmp");
	teapot->setAnimation(Animation(Keyframe(glm::vec4(0, 1, 0, 90), 1), true));
	teapot->SetShaders(phong_shaders);
	teapot->Move(3, 0.2, 0);
	teapot->setAnimation(CreateMovementAnimation());

	std::vector<Object*> objects = CreateBaseObjects();
	//objects.push_back(teapot);

	delete shiny_mat;

	return objects;
}

