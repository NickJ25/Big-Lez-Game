#include "ControlsMenu.h"
#include <iostream>
#include "Input.h"
#include "GLFW/glfw3.h"

ControlsMenu::ControlsMenu()
{
}

void ControlsMenu::handle(Menu * menu)
{
	std::cout << "Options"
		<< "\n (1) Back "<< std::endl;
	selectedMenu = menu;
}

void ControlsMenu::update()
{
	if (Input::keyboard1.keys[GLFW_KEY_1] && Input::keyboard1.keys[GLFW_KEY_UP]) {
		selectedMenu->setCurrent(selectedMenu->getOptions());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}
}

void ControlsMenu::draw()
{

}
