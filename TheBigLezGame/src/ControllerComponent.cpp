#include "ControllerComponent.h"
#include <iostream>

ControllerComponent::ControllerComponent(Input::ControllerType control) : m_controllerType(control)
{
}

bool ControllerComponent::getPrimaryAction()
{
	if (m_controllerType == Input::KEYBOARD) return Input::mouse1.buttons[GLFW_MOUSE_BUTTON_LEFT];
	else {
		if (Input::controller1.triggers.y < 0) return true;
		else return false;
	}
}

bool ControllerComponent::getSecondaryAction()
{
	if (m_controllerType == Input::KEYBOARD) return Input::mouse1.buttons[GLFW_MOUSE_BUTTON_RIGHT];
	else {
		if (Input::controller1.triggers.x > 0) return true;
		else return false;
	}
}

bool ControllerComponent::getReloadAction()
{
	if (m_controllerType == Input::KEYBOARD) return Input::keyboard1.keys[GLFW_KEY_R];
	else return Input::controller1.buttons[2];
}

bool ControllerComponent::getForwardMovement()
{
	if (m_controllerType == Input::KEYBOARD) return Input::keyboard1.keys[GLFW_KEY_W];
	else {
		
		if (Input::controller1.leftThumb.y > 0.3) return true;
		else return false;
	}
}

bool ControllerComponent::getLeftMovement()
{
	if (m_controllerType == Input::KEYBOARD) return Input::keyboard1.keys[GLFW_KEY_A];
	else {
		
		if (Input::controller1.leftThumb.x < -0.3) return true; 
		else return false;
	}
}

bool ControllerComponent::getRightMovement()
{
	if (m_controllerType == Input::KEYBOARD) return Input::keyboard1.keys[GLFW_KEY_D];
	else {
		if (Input::controller1.leftThumb.x > 0.3) return true; 
		else return false;
	}
}

bool ControllerComponent::getBackMovement()
{
	if (m_controllerType == Input::KEYBOARD) return Input::keyboard1.keys[GLFW_KEY_S];
	else {
		
		if (Input::controller1.leftThumb.y < -0.3) return true; 
		else return false;
	}
}

float ControllerComponent::getLookXAxis()
{
	if (m_controllerType == Input::KEYBOARD) return Input::mouse1.current_Xpos;
	else {
		return Input::controller1.rightThumb.x;
	}
}

float ControllerComponent::getLookYAxis()
{
	if (m_controllerType == Input::KEYBOARD) return Input::mouse1.current_Ypos;
	else {
		return Input::controller1.rightThumb.y;
	}
}
