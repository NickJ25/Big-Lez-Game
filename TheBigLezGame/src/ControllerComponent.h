#pragma once
#include "Input.h"
#include "GLFW/glfw3.h"

class ControllerComponent {
	enum ControllerType;
private:
	ControllerType m_controllerType;
public:
	enum ControllerType {KEYBOARD, CONTROLLER1, CONTROLLER2};
	ControllerComponent(ControllerType control);
	~ControllerComponent();

	bool getPrimaryAction();
	bool getSecondaryAction();
	bool getReloadAction();

	// Movement
	bool getForwardMovement();
	bool getLeftMovement();
	bool getRightMovement();
	bool getBackMovement();

};
