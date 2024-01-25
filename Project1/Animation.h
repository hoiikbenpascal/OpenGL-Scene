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
	bool paused = false;

	vector<Keyframe> frames;

	glm::vec3 total_translation = glm::vec3();

	float deltaTime = 0;
	float totalTime = 0;
	int current_frame_index = 0;
	Keyframe* current_frame = nullptr;

	std::chrono::steady_clock::time_point currentTime;
	std::chrono::steady_clock::time_point prevTime = std::chrono::high_resolution_clock::now();

	void handle_frames();
	void handle_animating(glm::mat4* model);
	void handle_time();

public:

	glm::vec3* movement = nullptr;

	bool looped = false;
	bool finished = false;

	void Apply(glm::mat4* model);

	 
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

	~Animation() {
		delete current_frame;
	}

	void Restart(int timeStamp = 0);

	void SetKeyframes(vector<Keyframe> _frames) {
		this->frames = _frames;
	}

	void AddKeyframe(Keyframe frame) {
		frames.push_back(frame);
	}

	void SetAllpivots(glm::vec3 pivot);

	void pause() {
		paused = true;
	}

	void unpause() {
		paused = false;
	}

	static std::chrono::steady_clock::time_point startTime;
};

