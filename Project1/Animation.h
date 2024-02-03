#pragma once
#include <vector>
#include <iostream>
#include <map>
#include "Keyframe.h"
#include "glsl.h"
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_mat.hpp>
#include <chrono>


class Animation
{
	bool started = false;
	std::chrono::steady_clock::time_point startTime;


	vector<Keyframe> frames;

	void start_animation(Keyframe* frame);

	static void Apply_frame(glm::mat4* model, float delta_time, const Keyframe* current_frame, bool repeated = false, glm::vec3* movement = nullptr);

	float handle_time(std::chrono::high_resolution_clock::time_point);
	void handle_animating(glm::mat4* model, float total_elapsed_time, Keyframe* frame);
	
	//applies all the previos keyframes and returns te time that was left over after applying the animations
	float apply_prev_frames(glm::mat4* model, float total_elapsed_time, Keyframe* frame);

public:

	glm::vec3* movement = nullptr;

	bool looped = false;
	bool finished = false;

	glm::mat4 Apply(const glm::mat4* base_model);

	Animation() {};

	Animation(Keyframe frame, bool loop = false) {
		frames = vector<Keyframe>(1);
		frames[0] = frame;
		looped = loop;
	}

	Animation(vector<Keyframe> _frames, bool loop = false)
	{
		this->frames = _frames;
		looped = loop;
	};

	void Restart(int timeStamp = 0);

	void SetKeyframes(vector<Keyframe> _frames) {
		this->frames = _frames;
	}

	void AddKeyframe(Keyframe frame) {
		frames.push_back(frame);
	}

	void SetAllpivots(glm::vec3 pivot);

};

