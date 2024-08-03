#pragma once
#include "Camera.h"

class InputHandler
{
	Camera* camera;
	int prev_x = 0;
	int prev_y = 0;


	float mouseSpeed = 0.05f;
public:

	InputHandler(Camera* camera) {
		this->camera = camera;
	}

	int start_y = 0;
	int start_x = 0;

	InputHandler() {}

	void HandleKeyboard(unsigned char key);
	void HandleMouse(int x, int y);
};

