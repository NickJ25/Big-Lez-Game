#include "ControllerComponent.h"

ControllerComponent::ControllerComponent(ControllerType control)
{

}

bool ControllerComponent::getPrimaryAction()
{
	return Input::mouse1.buttons[GLFW_MOUSE_BUTTON_LEFT];
}

bool ControllerComponent::getSecondaryAction()
{
	return Input::mouse1.buttons[GLFW_MOUSE_BUTTON_RIGHT];
}

bool ControllerComponent::getReloadAction()
{
	return Input::keyboard1.keys[GLFW_KEY_R];
}
