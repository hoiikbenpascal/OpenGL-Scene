#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>;
#include <glm/gtc/type_ptr.hpp>;

#include "glsl.h";

const float NearPlane = 0.1f;
const float FarPlane = 100000;
const float FoV = 45;

void Camera::SetProjection(int WIDTH, int HEIGHT)
{
	Projection = glm::perspective(glm::radians(FoV),
		1.0f * WIDTH / HEIGHT, NearPlane,
		FarPlane);
}

glm::mat4 Camera::GetView()
{
	return View;
}

glm::mat4* Camera::GetViewPointer()
{
	return &View;
}

glm::mat4 Camera::GetProjection()
{
	return Projection;
}

glm::mat4* Camera::GetProjectionPointer()
{
	return &Projection;
}

void Camera::SetLightPos(glm::vec3 new_pos)
{
	light_pos = new_pos;
}

glm::vec3 Camera::GetLightPos()
{
	return light_pos;
}

glm::vec3 Camera::GetPos()
{
	return pos;
}

void Camera::DroneMode() {
	Walkpos = pos;
	WalklookingAt = lookingAt;
	Walkoriantation = oriantation;

	pos = glm::vec3(0, 5.1, -20.0);
	lookingAt = glm::vec3(0, -1, 10);
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
	//drone mode
	glm::vec3 total = glm::normalize(pos - lookingAt) * movement;

	if (Mode) {
		//walk mode
		total.y = 0;
	}
	pos -= total;
	lookingAt -= total;
}

void Camera::Backward(float movement)
{
	glm::vec3 total = glm::normalize(pos - lookingAt) * movement;

	if (Mode) {
		//walk mode
		total.y = 0;
	}
	pos += total;
	lookingAt += total;
}

void Camera::Left(float movement) {
	glm::vec3 dir = glm::normalize(pos - lookingAt);
	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 right = glm::normalize(glm::cross(up, dir));

	if (Mode) {
		//walk mode
		right.y = 0;
	}

	pos -= right;
	lookingAt -= right;
}

void Camera::Right(float movement) {
	glm::vec3 dir = glm::normalize(pos - lookingAt);
	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 right = glm::normalize(glm::cross(up, dir));

	if (Mode) {
		//walk mode
		right.y = 0;
	}

	pos += right;
	lookingAt += right;
}

void Camera::MoveUp(float movement) {
	//walkmode can't go up
	if (Mode) { return; }
	pos += oriantation * movement;
	lookingAt += oriantation * movement;
}

void Camera::MoveDown(float movement) {
	//walkmode can't go down
	if (Mode) { return; }
	pos -= oriantation * movement;
	lookingAt -= oriantation * movement;
}

void Camera::lookAround(float x, float y)
{
	glm::vec3 dir = glm::normalize(pos - lookingAt);
	glm::vec3 up = glm::vec3(0, 1, 0);
	lookingAt += (glm::normalize(glm::cross(up, dir)) * x);
	lookingAt[1] += y;
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


