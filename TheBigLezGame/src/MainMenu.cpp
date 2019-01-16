#include "MainMenu.h"
#include <iostream>
#include <SDL.h>
#include "Image.h"


void MainMenu::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
		if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
}

MainMenu::MainMenu()
{

}

void MainMenu::handle(Menu * menu)
{
	std::cout << "Main Menu"
		<< "\n (1) Singleplayer "
		<< "\n (2) Options"
		<< "\n (3) Quit " << std::endl;
	background = new Image("assets/Art/tempBackground.png", glm::vec2(640.0, 360.0));
	buttonTest = new Button(glm::vec2(640.0, 360.0), "Singleplayer");
	testText = new Text(glm::vec2(5.0, 5.0), "assets/Fonts/ariali.ttf");
	testText->scale(glm::vec2(0.5, 0.5));

	selectedMenu = menu;
	//selectedMenu->setCurrent(selectedMenu->getSinglePlayer());
	//selectedMenu->getCurrentState()->handle(selectedMenu);

}

void MainMenu::update()
{
	//int state = glfwGetKey(window, GLFW_KEY_E) {

	//}
	//const Uint8 *keys = SDL_GetKeyboardState(NULL);
	//if (keys[SDL_SCANCODE_1]) {
	//	selectedMenu->setCurrent(selectedMenu->getSinglePlayer());
	//	selectedMenu->getCurrentState()->handle(selectedMenu);
	//}
	//if (keys[SDL_SCANCODE_2]) {
	//	selectedMenu->setCurrent(selectedMenu->getOptions());
	//	selectedMenu->getCurrentState()->handle(selectedMenu);
	//}
	//if (keys[SDL_SCANCODE_3]) {
	//	SDL_Quit();
	//	exit(0);
	//}
}

void MainMenu::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	background->draw();
	buttonTest->draw();
	testText->draw("Developed by Group 3", glm::vec3(1.0,1.0,1.0));
}
