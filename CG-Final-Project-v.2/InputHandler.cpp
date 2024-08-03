#include "InputHandler.h"
#include <glm/gtc/type_ptr.hpp>;

#include "glsl.h";
#include <GL/freeglut_std.h>

void InputHandler::Reset() {
	prev_x = 0;
	prev_y = 0;
}

void InputHandler::HandleMouse(int x, int y)
{
	if (prev_x == 0) {
		prev_x = x;
	}

	if (prev_y == 0) {
		prev_y = y;
	}

	int delta_x = x - prev_x;
	int delta_y = y - prev_y;

	camera->lookAround(delta_x * mouseSpeed, delta_y * mouseSpeed);

	prev_x = x;
	prev_y = y;

	camera->UpdateView();
}

void InputHandler::HandleKeyboard(unsigned char key)
{
	switch (key) {
		//escape
	case 27:
		glutExit();
		break;
		//move the camera
	case 'w':
		camera->Forward();
		break;
	case 'W':
		camera->Forward();
		break;
	case 's':
		camera->Backward();
		break;
	case 'S':
		camera->Backward();
		break;
	case 'a':
		camera->Left();
		break;
	case 'A':
		camera->Left();
		break;
	case 'd':
		camera->Right();
		break;
	case 'D':
		camera->Right();
		break;
	case ' ':
		camera->MoveUp();
		break;
	case 'x':
		camera->MoveDown();
		break;
	case 'X':
		camera->MoveDown();
		break;

		//roatate the camera
	case 'i':
		camera->LookUp();
		break;
	case 'I':
		camera->LookUp();
		break;
	case 'j':
		camera->LookLeft();
		break;
	case 'J':
		camera->LookLeft();
		break;
	case 'k':
		camera->LookDown();
		break;
	case 'K':
		camera->LookDown();
		break;
	case 'l':
		camera->LookRight();
		break;
	case 'L':
		camera->LookRight();
		break;

		//switch the cameras
	case 'v':
		camera->toggle();
		break;
	}

	camera->UpdateView();
}

