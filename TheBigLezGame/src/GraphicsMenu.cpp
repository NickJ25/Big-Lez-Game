#include "GraphicsMenu.h"

GraphicsMenu::GraphicsMenu()
{
}

void GraphicsMenu::handle(Menu * menu)
{
	background = new Image("assets/Art/tempBackground.png", glm::vec2(640.0, 360.0));
	selectedMenu = menu;
	backBtn = new Button(Button::NORMAL, glm::vec2(640.0, 100.0), "Back");
	resolutionBtn = new Button(Button::NORMAL, glm::vec2(640.0, 580.0), "");
	antiAlisBtn = new Button(Button::NORMAL, glm::vec2(640.0, 460.0), "");
	applyBtn = new Button(Button::NORMAL, glm::vec2(640.0, 240.0), "Apply");

	leftResoBtn = new Button(Button::ARROW, glm::vec2(420.0, 580.0), "");
	rightResoBtn = new Button(Button::ARROW, glm::vec2(850.0, 580.0), "");
	rightResoBtn->rotate(180);

	leftAABtn = new Button(Button::ARROW, glm::vec2(420.0, 460.0), "");
	rightAABtn = new Button(Button::ARROW, glm::vec2(850.0, 460.0), "");
	rightAABtn->rotate(180);
	m_window = glfwGetCurrentContext();

	resolutionTxt = new Text(glm::vec2(560.0, 570.0), "assets/Fonts/ariali.ttf");
	resolutionTxt->scale(glm::vec2(0.8, 0.8));
}

void GraphicsMenu::update()
{
	if (backBtn->buttonClick()) {
		selectedMenu->setCurrent(selectedMenu->getOptions());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}

	if (leftResoBtn->buttonClick()) {
		resoMode--;
		if (resoMode < 0) {
			resoMode = 2;
		}
	}

	if (rightResoBtn->buttonClick()) {
		resoMode++;
		if (resoMode > 2) {
			resoMode = 0;
		}
	}

	if (leftAABtn->buttonClick()) {
		aaMode--;
		if (aaMode < 0) {
			aaMode = 2;
		}
	}

	if (rightAABtn->buttonClick()) {
		aaMode++;
		if (aaMode > 2) {
			aaMode = 0;
		}
	}

	switch (resoMode) {
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

	switch (aaMode) {
	case 0:

		break;
	case 1:

		break;
	case 2:

		break;
	}

	//std::cout << mode << " " << newWidth << "x" << newHeight << std::endl;
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
	antiAlisBtn->draw();
	applyBtn->draw();
	leftResoBtn->draw();
	rightResoBtn->draw();
	leftAABtn->draw();
	rightAABtn->draw();
	std::string t_Test = (std::to_string(newWidth) + "x" + std::to_string(newHeight));
	resolutionTxt->draw(t_Test, glm::vec4(1.0, 1.0, 1.0, 1.0),1);
}
