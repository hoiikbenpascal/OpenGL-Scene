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
	vector<Keyframe> frames;

	float deltaTime;
	float totalTime;
	int currentKeyframe = 0;

	std::chrono::steady_clock::time_point currentTime;
	std::chrono::steady_clock::time_point prevTime = std::chrono::high_resolution_clock::now();

public:

	void Apply(glm::mat4* model);

	bool finished = false;
	bool looped = false;
	 
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


	void Restart(int timeStamp = 0) {
		currentKeyframe = 0;
		prevTime = std::chrono::high_resolution_clock::now();
		Animation::startTime = std::chrono::high_resolution_clock::now();
		finished = false;
		totalTime = 0;
	}

	void SetKeyframes(vector<Keyframe> frames) {
		this->frames = frames;
	}

	void AddKeyframe(Keyframe frame) {
		frames.push_back(frame);
	}

	void SetAllpivots(glm::vec3 pivot);
	static std::chrono::steady_clock::time_point startTime;
};

