#include "Input.h"
Input::Keyboard Input::keyboard1;
Input::Mouse Input::mouse1;
Input::Controller Input::controller1;
Input::Controller Input::controller2;
int Input::SCREEN_HEIGHT;
int Input::SCREEN_WIDTH;

bool Input::determineInput(ControllerType controllerType, int key)
{
	switch (controllerType)
	{
	case KEYBOARD:
		return (keyboard1.keys[key]);
		break;
	case CONTROLLER1:
		return controller1.buttons[key];
		break;
	case CONTROLLER2:
		return controller2.buttons[key];
		break;
	default:
		return false;
		break;
	}
}
