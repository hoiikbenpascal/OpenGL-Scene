#include "Animation.h"
#include <glm/gtc/matrix_transform.hpp>
//set the start time of the program
std::chrono::steady_clock::time_point Animation::startTime = std::chrono::high_resolution_clock::now();

void Animation::Apply(glm::mat4* model)
{
	if (looped && finished) {
		Restart();
	}

	//check if the animation is finished
	if (currentTimeStamp >= timestamps.size()) {
		finished = true;
		prevTime = currentTime;
		return;
	}

	//calculate the time diffrence and the total passed time
	currentTime = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - prevTime).count();
	totalTime += deltaTime;

	glm::mat4 identity = glm::mat4(1.0f);

	//if the current timestamp is passed proceed to the next one
	if (totalTime >= timestamps[currentTimeStamp]) {
		currentTimeStamp++;
	}
	if (scale.size() > currentTimeStamp) {
		*model *= glm::scale(*model, scale[currentTimeStamp] * deltaTime);
	}
	if (transform.size() > currentTimeStamp) { 
		*model = glm::translate(identity, transform[currentTimeStamp] * deltaTime) * *model;
	}
	if (rotation.size() > currentTimeStamp) {
		*model = glm::rotate(*model, glm::radians(rotation[currentTimeStamp].w * deltaTime), glm::vec3(rotation[currentTimeStamp].x, rotation[currentTimeStamp].y, rotation[currentTimeStamp].z));
	}

	prevTime = currentTime;

}
