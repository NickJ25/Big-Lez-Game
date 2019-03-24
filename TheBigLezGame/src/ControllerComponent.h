#pragma once
#include "Input.h"
#include "GLFW/glfw3.h"

class ControllerComponent {
private:

public:
	enum ControllerType {KEYBOARD, CONTROLLER1, CONTROLLER2};
	ControllerComponent(ControllerType control);
	~ControllerComponent();

	bool getPrimaryAction();
	bool getSecondaryAction();
	bool getReloadAction();

};
