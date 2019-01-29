#include "GraphicsMenu.h"

GraphicsMenu::GraphicsMenu()
{
}

void GraphicsMenu::handle(Menu * menu)
{
	background = new Image("assets/Art/tempBackground.png", glm::vec2(640.0, 360.0));
	selectedMenu = menu;
	backBtn = new Button(glm::vec2(640.0, 100.0), "Back");
	resolutionBtn = new Button(glm::vec2(640.0, 580.0), "Change");
	applyBtn = new Button(glm::vec2(640.0, 240.0), "Apply");
	m_window = glfwGetCurrentContext();

	resolutionTxt = new Text(glm::vec2(640.0, 600.0), "assets/Fonts/ariali.ttf");
	resolutionTxt->scale(glm::vec2(0.8, 0.8));
}

void GraphicsMenu::update()
{
	if (backBtn->buttonClick()) {
		selectedMenu->setCurrent(selectedMenu->getOptions());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}

	if (resolutionBtn->buttonClick()) {
		mode++;
		if (mode > 2) {
			mode = 0;
		}
	}

	switch (mode) {
	case 0:
		newWidth = 640;
		newHeight = 360;
		break;
	case 1:
		newWidth = 1280;
		newHeight = 720;
		break;
	case 2:
		newWidth = 1920;
		newHeight = 1080;
		break;
	}

	std::cout << mode << " " << newWidth << "x" << newHeight << std::endl;
	if (applyBtn->buttonClick()) {
		glfwSetWindowSize(m_window, newWidth, newHeight);
	}
	//glfwSetWindowSize
}

void GraphicsMenu::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	background->draw();
	backBtn->draw();
	resolutionBtn->draw();
	applyBtn->draw();
	std::string t_Test = newWidth + "x" + newHeight;
	resolutionTxt->draw(t_Test.c_str(), glm::vec3(1.0, 1.0, 1.0));
}
