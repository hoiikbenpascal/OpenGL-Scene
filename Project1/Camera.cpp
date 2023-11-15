#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>;
#include <glm/gtc/type_ptr.hpp>;

#include "glsl.h";

void Camera::SetProjection(int WIDTH, int HEIGHT)
{
	Projection = glm::perspective(glm::radians(45.0f),
		1.0f * WIDTH / HEIGHT, 0.1f,
		50.0f);
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
	lookingAt = glm::vec3(0.0, 0.5, 0.0);
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


