#include "Animation.h"
#include <glm/gtc/matrix_transform.hpp>

void Animation::Apply(glm::mat4* model)
{
	Keyframe currentFrame = frames[frame_index];

	if (!started) {
		start_animation(&currentFrame);
	}

	float delta_time = next_frame_if_finished(&currentFrame, model);

	//check if animation is finished and loop it if needed
	if (finished) {
		if (looped) {
			Restart();
		}
		return;
	}

	currentFrame.Apply(model, delta_time);
}

/// <summary>
/// Goes to the next frame if the previus keyframe is finished
/// also applies the remainder of the keyframes animation
/// </summary>
/// <param name="current_frame"></param>
/// <param name="model"></param>
/// <returns>The time to apply the current animation with</returns>
float Animation::next_frame_if_finished(Keyframe* current_frame, glm::mat4* model) {

	float frame_time = timer.GetFrameTimeSeconds();

	// If the current keyframe is NOT finished
	if (frame_time < current_frame->time) {
		// just return delta time
		return timer.SecondsSinceLastFrame();
	}

	// Otherwise go to the next frame

	// Timer synching
	float frame_overtime = frame_time - current_frame->time;
	timer.SetLastFrameFinishedTime(frame_overtime);

	// Apply the last bit of the frame
	float remaining_frame_time = timer.SecondsSinceLastFrame() - frame_overtime;
	current_frame->Apply(model, remaining_frame_time);

	//Go to the next frame
	frame_index++;
	//if all frames are finished
	if (frame_index >= frames.size()) {
		finished = true;
		return 0;
	}

	current_frame = &(frames[frame_index]);
	return frame_overtime - remaining_frame_time;
}

void Animation::start_animation(Keyframe* frame) {
	started = true;
	*frame = frames[0];
	frame_index = 0;
	timer.Start();
}

void Animation::Restart(int timeStamp)
{
	finished = false;
	started = false;
	frame_index = 0;
}

Animation Animation::FlipRotation() {
	Animation animation = *this;
	for (int frame = 0; frame < frames.size(); frame++) {
		Keyframe currFrame = frames[frame];
		currFrame.GetRotation()->w = -frames[frame].GetRotation()->w;
		animation.frames[frame] = currFrame;
	}
	return animation;
}

void Animation::SetAllpivots(glm::vec3 pivot)
{
	for (Keyframe frame : frames) {
		//need to += because of the pivoting that's done in the set_total_translation_and_pivots function
		*(frame.GetPivot()) += pivot;
	}
}