#include "Animation.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Animation::Apply(const glm::mat4* base_model)
{

	Keyframe currentFrame;

	glm::mat4 model = *base_model;

	if (!started) {
		start_animation(&currentFrame);
	}

	//updates the time
	float total_elapsed_time = handle_time(startTime);

	//currentFrame should change here
	//handle_frames(total_elapsed_time, frame);

	//does the actual moving of the mesh
	handle_animating(&model, total_elapsed_time, &currentFrame);

	//check if animation is finished and loop it if needed
	if (finished) {
		if (looped) {
			Restart();
		}
	}

	return model;

}

void Animation::start_animation(Keyframe* frame) {
		startTime = std::chrono::high_resolution_clock::now();
		started = true;
		*frame = frames[0];
}

Animation Animation::FlipRotation() {
	Animation animation = *this;
	for (int frame = 0; frame < frames.size(); frame++) {
		Keyframe currFrame = frames[frame];
		currFrame.rotation.w = -frames[frame].rotation.w;
		animation.frames[frame] = currFrame;
	}
	return animation;
}

void Animation::Restart(int timeStamp)
{
	finished = false;
	started = false;
}

void Animation::SetAllpivots(glm::vec3 pivot)
{
	for (Keyframe frame : frames) {
		//need to += because of the pivoting that's done in the set_total_translation_and_pivots function
		frame.pivot += pivot;
	}
}

float Animation::handle_time(std::chrono::high_resolution_clock::time_point startTime) {

	std::chrono::steady_clock::time_point currentTime = std::chrono::high_resolution_clock::now();

	//calculate the total elapsed time since the animation started
	float total_elapsed_time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
	return total_elapsed_time;
}


void Animation::handle_animating(glm::mat4* model, float total_elapsed_time, Keyframe* frame)
{

	float elapsed_time = 0;
	int current_frame_index = 0;

	//apply all the previos frames
	while (current_frame_index < frames.size() && elapsed_time + frames[current_frame_index].time < total_elapsed_time)
	{
		*frame = frames[current_frame_index];

		Apply_frame(model, frame->time, frame, true);
		elapsed_time += frame->time;
		current_frame_index++;
	}

	if (current_frame_index >= frames.size()) {
		finished = true;
		return;
	}

	*frame = frames[current_frame_index];
	//apply the current frame based on the time between the frames
	Apply_frame(model, total_elapsed_time - elapsed_time , frame, false);

}

void Animation::Apply_frame(glm::mat4* model, float delta_time, const Keyframe* current_frame, bool repeated) {

	const glm::vec3 empty;
	const glm::vec4 empty4;

	//scale
	if (current_frame->scale != empty) {
		*model *= glm::scale(*model, current_frame->scale * delta_time);
	}

	//translate
	if (current_frame->translate != empty) {
		*model = glm::translate(glm::mat4(1.0f), current_frame->translate * delta_time) * *model;
	}

	//rotate
	if (current_frame->rotation != empty4) {
		//if the pivot is empty use the standard function
		if (current_frame->pivot == empty) {
			*model = glm::rotate(*model, glm::radians(current_frame->rotation.w * delta_time), glm::vec3(current_frame->rotation.x, current_frame->rotation.y, current_frame->rotation.z));
		}
		else {
			//translate the model to the pivot point, rotate it and translate it back
			*model = glm::translate(*model, current_frame->pivot);
			*model = glm::rotate(*model, glm::radians(current_frame->rotation.w * delta_time), glm::vec3(current_frame->rotation.x, current_frame->rotation.y, current_frame->rotation.z));
			*model = glm::translate(*model, -(current_frame->pivot));
		}
	}

}