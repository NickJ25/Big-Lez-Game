#pragma once
#include <string>
#include <glm/glm.hpp>

class Input
{
public:
	static enum ControllerType { KEYBOARD, CONTROLLER1, CONTROLLER2 };
private:

	struct Keyboard {
		bool keys[1024];
		ControllerType type;
	};

	struct Mouse {
		bool buttons[16];
		int current_Xpos, current_Ypos;
		bool Press, Release;
		ControllerType type;
	};

	struct Controller {
		std::string name;
		bool connected;
		bool buttons[15];
		glm::vec2 leftThumb;
		glm::vec2 rightThumb;
		glm::vec2 triggers;
		ControllerType type;
	};

public:

	static Keyboard Input::keyboard1;
	static Mouse Input::mouse1;
	static Controller Input::controller1;
	static Controller Input::controller2;
	static int SCREEN_HEIGHT;
	static int SCREEN_WIDTH;
	//static bool Input::keys[1024];
	//static int Input::mouse_xpos;
	//static int Input::mouse_ypos;

};