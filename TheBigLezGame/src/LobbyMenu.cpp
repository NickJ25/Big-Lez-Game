#include "LobbyMenu.h"

void LobbyMenu::addController(Input::ControllerType controller)
{
	if (playerList[0] == nullptr)
	{
		std::cout << "Player 1 setup \n";
		playerList[0] = new Player::Character();
		playerList[0]->control = controller;
	}	
	else if(playerList[1] == nullptr) {
		std::cout << "Player 2 setup \n";
		playerList[1] = new Player::Character();
		playerList[1]->control = controller;
	}
}

LobbyMenu::LobbyMenu()
{

}

void LobbyMenu::handle(Menu * menu)
{
	// Reset Controller Usage
	keyboardInUse = false;
	controller1InUse = false;
	controller2InUse = false;
	playerList = { nullptr, nullptr };

	background = new Image("assets/Art/tempBackground.png", glm::vec2(640.0, 360.0));
	m_window = glfwGetCurrentContext();
	backBtn = new Button(Button::NORMAL, glm::vec2(640.0, 100.0), "Back");
	startBtn = new Button(Button::NORMAL, glm::vec2(640.0, 340.0), "Start");

	p1BtnLeft = new Button(Button::ARROW, glm::vec2(160.0, 340.0), "");
	p1BtnRight = new Button(Button::ARROW, glm::vec2(320.0, 340.0), "");
	p1BtnRight->rotate(180.0);
	p2BtnLeft = new Button(Button::ARROW, glm::vec2(640.0, 340.0), "");
	p2BtnRight = new Button(Button::ARROW, glm::vec2(800.0, 340.0), "");
	p2BtnRight->rotate(180.0);

	

	selectedMenu = menu;
}

void LobbyMenu::update() 
{
	// Check input devices for input to assign players
	if (Input::keyboard1.keys[GLFW_KEY_SPACE] && !keyboardInUse) {
		keyboardInUse = true;
		addController(Input::KEYBOARD);
	}

	if (Input::controller1.buttons[0] && !controller1InUse) {
		controller1InUse = true;
		addController(Input::CONTROLLER1);
	}

	if (Input::controller2.buttons[0] && !controller2InUse) {
		controller2InUse = true;
		addController(Input::CONTROLLER2);
	}

	if (playerList[0] == nullptr) {
		cout << "Press Space or A for Player 1 \n";
	}
	else {
		if (p1BtnLeft->buttonClick()) {
			p1Choice++;
		}
		if (p1BtnRight->buttonClick()) {
			p1Choice--;
		}
		if (p1Choice < 0) p1Choice = characterList.size();
		if (p1Choice > characterList.size()) p1Choice = 0;
	}

	if (playerList[1] == nullptr) {
		cout << "Press Space or A for Player 2 \n";
	}
	else {
		if (p2BtnLeft->buttonClick()) {
			p2Choice++;
		}
		if (p2BtnRight->buttonClick()) {
			p2Choice--;
		}
		if (p2Choice < 0) p2Choice = characterList.size();
		if (p2Choice > characterList.size()) p2Choice = 0;
	}

	if (backBtn->buttonClick()) {
		selectedMenu->setCurrent(selectedMenu->getMainMenu());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}

	if (startBtn->buttonClick()) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		selectedMenu->setCurrent(selectedMenu->getSinglePlayer());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}
}

void LobbyMenu::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	background->draw();

	if (playerList[0] != nullptr) {
		p1BtnLeft->draw();
		p1BtnRight->draw();
	}

	if (playerList[1] != nullptr) {
		p2BtnLeft->draw();
		p2BtnRight->draw();
	}

	backBtn->draw();
	startBtn->draw();
}