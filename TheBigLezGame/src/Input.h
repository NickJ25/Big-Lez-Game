#pragma once

class Input
{
private:
	struct Keyboard {
		bool keys[1024];
	};

	struct Mouse {
		bool buttons[16];
		int current_Xpos, current_Ypos;
		float offset_Xpos, offset_Ypos;
		bool Press, Release;
	};
public:
	static Keyboard Input::keyboard1;
	static Mouse Input::mouse1;
	//static bool Input::keys[1024];
	//static int Input::mouse_xpos;
	//static int Input::mouse_ypos;

};