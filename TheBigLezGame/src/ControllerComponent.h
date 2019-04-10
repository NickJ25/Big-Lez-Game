#pragma once
#include "Input.h"
#include "GLFW/glfw3.h"

class ControllerComponent {
private:
	Input::ControllerType m_controllerType;
public:
	ControllerComponent(Input::ControllerType control);
	~ControllerComponent();

	bool getPrimaryAction();
	bool getSecondaryAction();
	bool getReloadAction();

	// Movement
	bool getForwardMovement();
	bool getLeftMovement();
	bool getRightMovement();
	bool getBackMovement();
	float getLookXAxis();
	float getLookYAxis();

};
