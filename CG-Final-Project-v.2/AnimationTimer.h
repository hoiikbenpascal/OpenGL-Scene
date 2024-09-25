#pragma once
#include <chrono>
#include <iostream>;
class AnimationTimer
{
	std::chrono::steady_clock::time_point last_frame_time;
	std::chrono::steady_clock::time_point frame_finished_time;

public:
	AnimationTimer()
	{
	};


	float SecondsSinceLastFrame() {
		auto currentTime = std::chrono::steady_clock::now();
		float elapsedTime = std::chrono::duration<float>(currentTime - last_frame_time).count();
		last_frame_time = currentTime;
		return elapsedTime;
	}

	float GetFrameTimeSeconds() const {
		auto currentTime = std::chrono::steady_clock::now();
		float elapsedTime = std::chrono::duration<float>(currentTime - frame_finished_time).count();
		return elapsedTime;
	}

	void SetLastFrameFinishedTime(float frameOvertime) {
		auto currentTime = std::chrono::steady_clock::now();
		frame_finished_time = currentTime - ((std::chrono::seconds)((long)frameOvertime));
	}

	void Start() {
		last_frame_time = std::chrono::steady_clock::now();
		frame_finished_time = last_frame_time;
	}
};

