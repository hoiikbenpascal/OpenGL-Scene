#include "Animation.h"
#include <glm/gtc/matrix_transform.hpp>
//set the start time of the program
std::chrono::steady_clock::time_point Animation::startTime = std::chrono::high_resolution_clock::now();

void Animation::Apply(glm::mat4* model)
{

	//updates the time
	handle_time();

	//currentFrame should change here
	handle_frames();

	if (finished) {
		if (!looped) {
			prevTime = currentTime;
			return;
		}
		prevTime = currentTime;
		Restart();
		return;
	}

	//does the actual moving of the mesh
	handle_animating(model);

	prevTime = currentTime;

}

void Animation::Restart(int timeStamp)
{
	current_frame_index = 0;
	prevTime = std::chrono::high_resolution_clock::now();
	Animation::startTime = std::chrono::high_resolution_clock::now();
	finished = false;
	totalTime = 0;
	delete current_frame;
	current_frame = nullptr;
}

void Animation::SetAllpivots(glm::vec3 pivot)
{
	for (Keyframe frame : frames) {
		//need to += because of the pivoting that's done in the set_total_translation_and_pivots function
		frame.pivot += pivot;
	}
}

void Animation::handle_time() {
	//calculate the time diffrence and the total passed time
	currentTime = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - prevTime).count();
	totalTime += deltaTime;
}

void Animation::handle_frames()
{
	//check if the frame exists
	if (current_frame == nullptr) {
		//start witht he first frame
		//this pointer is destroyed when the animation is destroyed or reset
		current_frame = new Keyframe(frames[current_frame_index]);

		//set the initial movement in case the object was moved before the animation started
		if (movement != nullptr) {
			current_frame->pivot += *movement;
		}
	}


	//if the current timestamp is passed proceed to the next one0
	if (totalTime >= current_frame->time) {
		current_frame_index++;

		//restart the time counter since every keyframe has it's own time variable
		totalTime = 0;

		//check if the animation is finished 
		if (current_frame_index >= frames.size()) {
			finished = true;
			prevTime = currentTime;
			return;
		}

		*current_frame = frames[current_frame_index];

		//keep track of the total movement of the animation to make sure the rotation is pivoted properly
		if (movement != nullptr) {
			*movement += frames[current_frame_index - 1].translate * frames[current_frame_index - 1].time;
			current_frame->pivot += *movement;
		}

	}

}


void Animation::handle_animating(glm::mat4* model)
{
	const glm::vec3 empty;
	const glm::vec4 empty4;

	//scale
	if (current_frame->scale != empty) {
		*model *= glm::scale(*model, current_frame->scale * deltaTime);
	}

	//translate
	if (current_frame->translate != empty) {
		*model = glm::translate(glm::mat4(1.0f), current_frame->translate * deltaTime) * *model;
	}

	//rotate
	if (current_frame->rotation != empty4) {
		//if the pivot is empty use the standard function
		if (current_frame->pivot == empty) {
			*model = glm::rotate(*model, glm::radians(current_frame->rotation.w * deltaTime), glm::vec3(current_frame->rotation.x, current_frame->rotation.y, current_frame->rotation.z));
		}
		else {
			//translate the model to the pivot point, rotate it and translate it back
			*model = glm::translate(*model, current_frame->pivot);
			*model = glm::rotate(*model, glm::radians(current_frame->rotation.w * deltaTime), glm::vec3(current_frame->rotation.x, current_frame->rotation.y, current_frame->rotation.z));
			*model = glm::translate(*model, -(current_frame->pivot));
		}
	}
}