#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>;
#include <glm/gtc/type_ptr.hpp>;

#include "glsl.h";

const float NearPlane = 0.1f;
const float FarPlane = 1000;
const float FoV = 45;

void Camera::Move(unsigned char key) {
    switch (key) {
        //escape
    case 27:
        glutExit();
        break;
        //move the camera
    case 'w':
        Forward();
        break;
    case 'W':
        Forward();
        break;
    case 's':
        Backward();
        break;
    case 'S':
        Backward();
        break;
    case 'a':
        Left();
        break;
    case 'A':
        Left();
        break;
    case 'd':
        Right();
        break;
    case 'D':
        Right();
        break;
    case ' ':
        MoveUp();
        break;
    case 'x':
        MoveDown();
        break;
    case 'X':
        MoveDown();
        break;

        //roatate the camera
    case 'i':
        LookUp();
        break;
    case 'I':
        LookUp();
        break;
    case 'j':
        LookLeft();
        break;
    case 'J':
        LookLeft();
        break;
    case 'k':
        LookDown();
        break;
    case 'K':
        LookDown();
        break;
    case 'l':
        LookRight();
        break;
    case 'L':
        LookRight();
        break;

        //switch the cameras
    case 'v':
        toggle();
        break;
    }
}

void Camera::SetProjection(int WIDTH, int HEIGHT)
{
	Projection = glm::perspective(glm::radians(FoV),
		1.0f * WIDTH / HEIGHT, NearPlane,
		FarPlane);
}

glm::mat4 Camera::GetView()
{
	return glm::lookAt(pos, lookingAt, oriantation);
}

glm::mat4 Camera::GetProjection()
{
	return Projection;
}

void Camera::SetLightPos(glm::vec3 new_pos)
{
	light_pos = new_pos;
}

glm::vec3 Camera::GetLightPos()
{
	return light_pos;
}

void Camera::DroneMode() {
	Walkpos = pos;
	WalklookingAt = lookingAt;
	Walkoriantation = oriantation;

	pos = glm::vec3(2.0, 2.0, 8.0);
	lookingAt = glm::vec3(2.0, 2.0, 10.0);
	oriantation = glm::vec3(0.0, 1.0, 0.0);
}
void Camera::WalkMode() {
	pos = Walkpos;
	lookingAt = WalklookingAt;
	oriantation = Walkoriantation;
}

void Camera::toggle() {
	Mode = !Mode;
	if (Mode) {
		WalkMode();
		return;
	}
	DroneMode();
}

void Camera::Forward(float movement) {
		glm::vec3 total = glm::normalize(pos - lookingAt) * movement;
		pos -= total;
		lookingAt -= total;
}

void Camera::Backward(float movement)
{
		glm::vec3 total = glm::normalize(pos - lookingAt) * movement;
		pos += total;
		lookingAt += total;
}

void Camera::Left(float movement) {
	glm::vec3 dir = glm::normalize(pos - lookingAt);
	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 right = glm::normalize(glm::cross(up, dir));
	pos -= right;
	lookingAt -= right;
}

void Camera::Right(float movement) {
	glm::vec3 dir = glm::normalize(pos - lookingAt);
	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 right = glm::normalize(glm::cross(up, dir));
	pos += right;
	lookingAt += right;
}

void Camera::MoveUp(float movement) {
	pos += oriantation * movement;
	lookingAt += oriantation * movement;
}

void Camera::MoveDown(float movement) {
	pos -= oriantation * movement;
	lookingAt -= oriantation * movement;
}

void Camera::LookLeft(float movement) {
	glm::vec3 dir = glm::normalize(pos - lookingAt);
	glm::vec3 up = glm::vec3(0, 1, 0);
	lookingAt -= glm::normalize(glm::cross(up, dir));
}
void Camera::LookRight(float movement) {
	glm::vec3 dir = glm::normalize(pos - lookingAt);
	glm::vec3 up = glm::vec3(0, 1, 0);
	lookingAt += glm::normalize(glm::cross(up, dir));

}
void Camera::LookUp(float movement) {
	lookingAt[1] += movement;
}
void Camera::LookDown(float movement) {
	lookingAt[1] -= movement;
}


