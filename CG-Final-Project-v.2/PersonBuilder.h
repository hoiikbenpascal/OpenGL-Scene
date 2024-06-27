#pragma once
#include "PrimitiveObject.h"
#include "PrimitiveBuilder.h"
#include <vector>

static Animation CreateLegAnimation() {
	vector<Keyframe> frames = {
		Keyframe({0,0.5 / 0.2,0}, 0.2f),
		Keyframe({0,-0.5 / 0.5,0}, 0.5f),
		Keyframe({0,0,0}, 1.3f)
	};

	return Animation(frames, true);
}

static Animation CreateArmJumpAnimation() {
	vector<Keyframe> frames = {
	Keyframe({0,-0.25 / 0.2,0}, 0.2f),
	Keyframe({0,1 / 0.3,0}, 0.3f),
	Keyframe({0,-0.75 / 1.5 ,0}, 1.5f)
	};

	return Animation(frames, true);
}

static PrimitiveObject* CreatePerson() {

#pragma region Create constants

	const int mesh_ammount = 6;
	const glm::vec3 skin_color = glm::vec3(0.68f, 0.59f, 0.49f);
	const glm::vec3 jean_color = glm::vec3(0.42f, 0.43f, 0.91f);
	const glm::vec3 shirt_color = glm::vec3(0.256f, 0.161f, 0.156f);
	const float torsoSize = 1;

	const float armSize = 0.15;
	const float armheigth = 1.1f;

	const float legSize = 0.2f;
	const float legHeight = 1.5f;

#pragma endregion

#pragma region Create meshes

	PrimitiveMesh* meshes = new PrimitiveMesh[mesh_ammount]{
		*CreateSolidRect(legHeight, legSize, legSize, jean_color), //legs
		*CreateSolidRect(legHeight, legSize, legSize, jean_color),

		*CreateSolidRect(armheigth, armSize, armSize, skin_color), //arms
		*CreateSolidRect(armheigth, armSize, armSize, skin_color),

		*CreateSphere(0.4f, 20, 20, skin_color), //head

		*CreateSolidRect(torsoSize,torsoSize, torsoSize * 0.5f, shirt_color), //body

		////angle indicator
		//*CreateSolidRect(0.2,0.2, 10),
	};

#pragma endregion



#pragma region Set meshe locations

	meshes[0].Move(torsoSize * 0.25f, -torsoSize, legSize * (torsoSize * 0.5f)); //legs
	meshes[1].Move(torsoSize * -0.25f, -torsoSize, legSize * (torsoSize * 0.5f));

	meshes[2].Move(torsoSize * 0.5f + armSize * 0.5f, 0, 0); //arms
	meshes[2].Rotate(0, 1, 0, 180);

	meshes[3].Move(torsoSize * -0.5f - armSize * 0.5f, 0, 0);
	meshes[3].Rotate(0, 1, 0, 180);

	meshes[4].Move(0, 0.75f, 0); //head

#pragma endregion


#pragma region Animations


	Animation legJump = CreateLegAnimation();
	Animation armJump = CreateArmJumpAnimation();

	meshes[0].setAnimation(legJump);
	meshes[1].setAnimation(legJump);

	meshes[2].setAnimation(armJump);
	meshes[3].setAnimation(armJump);

#pragma endregion

	PrimitiveObject* person = new PrimitiveObject(meshes, mesh_ammount);

	return person;
}