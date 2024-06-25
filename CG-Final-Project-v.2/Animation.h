#pragma once
#include <vector>
#include <iostream>
#include <map>
#include "Keyframe.h"
#include "glsl.h"
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_mat.hpp>
#include <chrono>
#include "AnimationTimer.h"


class Animation
{
	bool started = false;
	AnimationTimer timer = AnimationTimer();


	void start_animation(Keyframe* frame);

	static void Apply_frame(glm::mat4* model, float delta_time, const Keyframe* current_frame, bool repeated = false);

	/// <summary>
	/// Calculates the elapsed time, and goes to the next frame if the time surpasses the frame time
	/// </summary>
	/// <returns> The remaining time to be applied to the current frame </returns>
	float next_frame_if_finished(Keyframe* current_frame, glm::mat4* model);

	void handle_animating(glm::mat4* model, float total_elapsed_time, Keyframe* frame);

	//applies all the previos keyframes and returns te time that was left over after applying the animations
	float apply_prev_frames(glm::mat4* model, float total_elapsed_time, Keyframe* frame);

public:

	bool looped = false;
	bool finished = false;
	int frame_index = 0;
	vector<Keyframe> frames;

	void Apply(glm::mat4* model);

	Animation() {};

	Animation(Keyframe const& frame, bool loop = false) {
		frames = vector<Keyframe>(1);
		frames[0] = frame;
		looped = loop;
	}

	Animation(vector<Keyframe> const& _frames, bool loop = false)
	{
		this->frames = _frames;
		looped = loop;
	};

	void Restart(int timeStamp = 0);

	void SetKeyframes(vector<Keyframe> const& _frames) {
		this->frames = _frames;
	}

	void AddKeyframe(Keyframe const& frame) {
		frames.push_back(frame);
	}

	void SetAllpivots(glm::vec3 pivot);

	Animation FlipRotation();
};

