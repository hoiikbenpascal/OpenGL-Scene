#pragma once
#include <glm/glm.hpp>;

class Camera
{
private:

	glm::vec3 light_pos;

	glm::vec3 pos;
	glm::vec3 lookingAt;
	glm::vec3 oriantation;

	glm::vec3 Walkpos;
	glm::vec3 WalklookingAt;
	glm::vec3 Walkoriantation;

	glm::mat4 Projection;

	//true is walk false is drone
	bool Mode = true;

	void DroneMode();
	void WalkMode();

public: 

	Camera() {
		pos = glm::vec3(2.0, 2.0, 8.0);
		lookingAt = glm::vec3(0.0, 0.5, 0.0);
		oriantation = glm::vec3(0.0, 1.0, 0.0);
	}
	Camera(glm::vec3 EyePosition, glm::vec3 center, glm::vec3 oriantation = glm::vec3(0.0, 1.0, 0.0)) {
		pos = EyePosition;
		Camera::lookingAt = center;
		Camera::oriantation = oriantation;
	}

	glm::mat4 GetView();
	void SetProjection(int WIDTH, int HEIGHT);
	glm::mat4 GetProjection();

	void SetLightPos(glm::vec3 new_pos);
	glm::vec3 GetLightPos();

	void toggle();

	void Move(unsigned char key);

	//camera movement
	void Forward(float movement = 1);
	void Backward(float movement = 1);
	void Left(float movement = 1);
	void Right(float movement = 1);
	void MoveUp(float movement = 1);
	void MoveDown(float movement = 1);

	//camera rotation
	void LookLeft(float movement = 1);
	void LookRight(float movement = 1);
	void LookUp(float movement = 1);
	void LookDown(float movement = 1);
};

