#include "Animation.h"
#include <glm/gtc/matrix_transform.hpp>
//set the start time of the program
std::chrono::steady_clock::time_point Animation::startTime = std::chrono::high_resolution_clock::now();

void Animation::Apply(glm::mat4* model)
{
	const glm::vec3 empty;
	const glm::vec4 empty4;

	if (finished) {
		if (!looped) {
			return;
		}
		Restart();
	}

	//calculate the time diffrence and the total passed time
	currentTime = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - prevTime).count();
	totalTime += deltaTime;

	glm::mat4 identity = glm::mat4(1.0f);

	//if the current timestamp is passed proceed to the next one
	if (totalTime >= frames[currentKeyframe].time) {
		currentKeyframe++;

		//restart the time counter since every keyframe has it's own time variable
		totalTime = 0;
	}

	//check if the animation is finished
	if (currentKeyframe >= frames.size()) {
		finished = true;
		prevTime = currentTime;
		return;
	}

	//scale
	if (frames[currentKeyframe].scale != empty) {
		*model *= glm::scale(*model, frames[currentKeyframe].scale * deltaTime); 
	}

	//translate
	if (frames[currentKeyframe].translate != empty) { 
		*model = glm::translate(identity, frames[currentKeyframe].translate * deltaTime) * *model;
	}

	//rotate
	if (frames[currentKeyframe].rotation != empty4) {
		//if the pivot is empty use the standard function
		if (frames[currentKeyframe].pivot != empty){
			*model = glm::rotate(*model, glm::radians(frames[currentKeyframe].rotation.w * deltaTime), glm::vec3(frames[currentKeyframe].rotation.x, frames[currentKeyframe].rotation.y, frames[currentKeyframe].rotation.z));
		}
		else {
			//translate the model to the pivot point, rotate it and translate it back
			*model = glm::translate(*model, frames[currentKeyframe].pivot);
			*model = glm::rotate(*model, glm::radians(frames[currentKeyframe].rotation.w * deltaTime), glm::vec3(frames[currentKeyframe].rotation.x, frames[currentKeyframe].rotation.y, frames[currentKeyframe].rotation.z));
			*model = glm::translate(*model, -frames[currentKeyframe].pivot);
		}
	}

	prevTime = currentTime;

}

void Animation::SetAllpivots(glm::vec3 pivot)
{
	for (Keyframe frame : frames) {
		frame.pivot = pivot;
	}
}
