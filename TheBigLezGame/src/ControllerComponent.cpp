#include "ControllerComponent.h"
#include <iostream>

ControllerComponent::ControllerComponent(ControllerType control) : m_controllerType(control)
{
}

bool ControllerComponent::getPrimaryAction()
{
	if (m_controllerType == KEYBOARD) return Input::mouse1.buttons[GLFW_MOUSE_BUTTON_LEFT];
	else {
		if (Input::controller1.triggers.y < 0) return true;
		else return false;
	}
}

bool ControllerComponent::getSecondaryAction()
{
	if (m_controllerType == KEYBOARD) return Input::mouse1.buttons[GLFW_MOUSE_BUTTON_RIGHT];
	else {
		if (Input::controller1.triggers.x > 0) return true;
		else return false;
	}
}

bool ControllerComponent::getReloadAction()
{
	if (m_controllerType == KEYBOARD) return Input::keyboard1.keys[GLFW_KEY_R];
	else return Input::controller1.buttons[2];
}

bool ControllerComponent::getForwardMovement()
{
	//if (m_controllerType == KEYBOARD) return Input::keyboard1.keys[GLFW_KEY_W];
	//else return Input::controller1.leftThumb.x;
	if (m_controllerType == KEYBOARD) return Input::keyboard1.keys[GLFW_KEY_W];
	else {
		
		if (Input::controller1.leftThumb.y > 0.3) { std::cout << "FORWARD" << std::endl; return true; }
		else return false;
	}
}

bool ControllerComponent::getLeftMovement()
{
	//if (m_controllerType == KEYBOARD) return Input::keyboard1.keys[GLFW_KEY_A];
	//else return Input::controller1.leftThumb.y;
	if (m_controllerType == KEYBOARD) return Input::keyboard1.keys[GLFW_KEY_A];
	else {
		
		if (Input::controller1.leftThumb.x < -0.3) { std::cout << "LEFT" << std::endl; return true; }
		else return false;
	}
}

bool ControllerComponent::getRightMovement()
{
	//if (m_controllerType == KEYBOARD) return Input::keyboard1.keys[GLFW_KEY_D];
	//else return Input::controller1.leftThumb.y;
	
	if (m_controllerType == KEYBOARD) return Input::keyboard1.keys[GLFW_KEY_D];
	else {
		if (Input::controller1.leftThumb.x > 0.3) { std::cout << "RIGHT" << std::endl; return true; }
		else return false;
	}
}

bool ControllerComponent::getBackMovement()
{
	//if (m_controllerType == KEYBOARD) return Input::keyboard1.keys[GLFW_KEY_S];
	//else return Input::controller1.leftThumb.x;
	if (m_controllerType == KEYBOARD) return Input::keyboard1.keys[GLFW_KEY_S];
	else {
		
		if (Input::controller1.leftThumb.y < -0.3) { std::cout << "BACK" << std::endl; return true; }
		else return false;
	}
}

float ControllerComponent::getLookXAxis()
{
	if (m_controllerType == KEYBOARD) return Input::mouse1.current_Xpos;
	else {
		return Input::controller1.rightThumb.x;
	}
}

float ControllerComponent::getLookYAxis()
{
	if (m_controllerType == KEYBOARD) return Input::mouse1.current_Ypos;
	else {
		return Input::controller1.rightThumb.y;
	}
}
