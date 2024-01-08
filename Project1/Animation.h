#pragma once
#include <vector>
#include "glsl.h"
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_mat.hpp>
#include <chrono>

class Animation
{
	vector<glm::vec3> transform;
	vector<glm::vec4> rotation;
	vector<glm::vec3> scale;

	vector<float> timestamps;

	float deltaTime;
	float totalTime;
	int currentTimeStamp = 0;


	std::chrono::steady_clock::time_point currentTime;
	std::chrono::steady_clock::time_point prevTime = std::chrono::high_resolution_clock::now();

public:

	void Apply(glm::mat4* model);
	bool finished = false;
	bool looped = false;
	 
	void SetTransform(vector<glm::vec3> transform) {
		this->transform = transform;
	}

	void Restart(int timeStamp = 0) {
		currentTimeStamp = 0;
		prevTime = std::chrono::high_resolution_clock::now();
		Animation::startTime = std::chrono::high_resolution_clock::now();
		finished = false;
		totalTime = 0;
	}

	void SetScale(vector<glm::vec3> scale) {
		this->scale = scale;
	}

	void SetRotation(vector<glm::vec4> rotation) {
		this->rotation = rotation;
	}

	void SetTimeStamps(vector<float> timeStamps) {
		this->timestamps = timeStamps;
	}

	static std::chrono::steady_clock::time_point startTime;
};

