#pragma once
#include <string>

class Input
{
private:
	struct Keyboard {
		bool keys[1024];
	};

	struct Mouse {
		bool buttons[16];
		int current_Xpos, current_Ypos;
		bool Press, Release;
	};

	struct Controller {
		std::string name;
		bool connected;
		bool buttons[15];
	};
public:
	static Keyboard Input::keyboard1;
	static Mouse Input::mouse1;
	static Controller Input::controller1;
	static Controller Input::controller2;
	//static bool Input::keys[1024];
	//static int Input::mouse_xpos;
	//static int Input::mouse_ypos;

};