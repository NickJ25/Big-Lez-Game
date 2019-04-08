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

void LobbyMenu::addCharacters()
{
	// Create Big Lez
	Player::Character BigLez;
	BigLez.fileLocation = "assets/Characters/BigLez/lez.dae";
	BigLez.name = "Leslie";
	BigLez.health = 100;
	BigLez.walkSpeed = 10;
	characterList.push_back(BigLez);
	//Image* bigLezPic = new Image("assets/Characters/BigLez/biglezPicture.png", glm::vec2(0, 0));
	//bigLezPic->scale(glm::vec2(500, 500));
	charPicList.push_back("assets/Characters/BigLez/biglezPicture.png");

	// Create Sassy
	Player::Character Sassy;
	Sassy.fileLocation = "assets/Characters/Sassy/sassy.dae";
	Sassy.name = "Sassy";
	Sassy.health = 100;
	Sassy.walkSpeed = 10;
	characterList.push_back(Sassy);
	//Image* sassyPic = new Image("assets/Characters/Sassy/sassyPicture.png", glm::vec2(0, 0));
	//sassyPic->scale(glm::vec2(0.2, 0.4));
	charPicList.push_back("assets/Characters/Sassy/sassyPicture.png");

	// Create Donny
	Player::Character Donny;
	Donny.fileLocation = "assets/Characters/Donny/donny.dae";
	Donny.name = "Donny";
	Donny.health = 100;
	Donny.walkSpeed = 10;
	characterList.push_back(Donny);
	//Image* donnyPic = new Image("assets/Characters/Donny/donnyPicture.png", glm::vec2(0, 0));
	//donnyPic->scale(glm::vec2(0.2, 0.4));
	charPicList.push_back("assets/Characters/Donny/donnyPicture.png");

	// Create Clarence
	Player::Character Clarence;
	//Clarence.fileLocation
	Clarence.name = "Clarence";
	Clarence.health = 100000;
	Clarence.walkSpeed = 12;
	Clarence.isLocked = true;
	characterList.push_back(Clarence);
	//Image* clarencePic = new Image("assets/Characters/Clarence/clarencePicture.png", glm::vec2(0, 0));
	//clarencePic->scale(glm::vec2(0.2, 0.4));
	charPicList.push_back("assets/Characters/Clarence/clarencePicture.png");

}

LobbyMenu::LobbyMenu()
{
	cout << "Created Characters!" << "\n";
	addCharacters();
}

void LobbyMenu::handle(Menu * menu)
{
	// Reset Controller Usage
	keyboardInUse = false;
	controller1InUse = false;
	controller2InUse = false;
	playerList = { nullptr, nullptr };

	background = new Image("assets/Art/background.png", glm::vec2(640.0, 360.0));
	m_window = glfwGetCurrentContext();
	backBtn = new Button(Button::NORMAL, glm::vec2(Input::SCREEN_WIDTH / 2, 100.0), "Back");
	startBtn = new Button(Button::NORMAL, glm::vec2(640.0, 340.0), "Start");

	// Buttons for character selection.
	p1BtnLeft = new Button(Button::ARROW, glm::vec2(Input::SCREEN_WIDTH * 0.125, Input::SCREEN_HEIGHT / 2), "");
	p1BtnRight = new Button(Button::ARROW, glm::vec2(Input::SCREEN_WIDTH * 0.375, Input::SCREEN_HEIGHT / 2), "");
	p1BtnRight->rotate(180.0);
	p2BtnLeft = new Button(Button::ARROW, glm::vec2(Input::SCREEN_WIDTH * 0.625, Input::SCREEN_HEIGHT / 2), "");
	p2BtnRight = new Button(Button::ARROW, glm::vec2(Input::SCREEN_WIDTH * 0.875, Input::SCREEN_HEIGHT / 2), "");
	p2BtnRight->rotate(180.0);

	// Text for Character selection
	p1CharacterSelected = new Text(glm::vec2(Input::SCREEN_WIDTH * 0.20, 5.0), "assets/Fonts/ariali.ttf");
	p2CharacterSelected = new Text(glm::vec2(Input::SCREEN_WIDTH * 0.80, 5.0), "assets/Fonts/ariali.ttf");
	p1InfoText = new Text(glm::vec2(Input::SCREEN_WIDTH * 0.20, 5.0), "assets/Fonts/ariali.ttf");
	p2InfoText = new Text(glm::vec2(Input::SCREEN_WIDTH * 0.80, 5.0), "assets/Fonts/ariali.ttf");
	selectedMenu = menu;
	p1CurrentCharPic = new Image(charPicList[p1Choice].c_str(), glm::vec2(0.0f, 0.0f));
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

	}
	else {
		if (p1BtnLeft->buttonClick()) {
			p1Choice--;
			if (p1Choice < 0) p1Choice = characterList.size() - 1;
		}
		if (p1BtnRight->buttonClick()) {
			p1Choice++;
			if (p1Choice > characterList.size() - 1) p1Choice = 0;
		}
		if (p1Choice < 0) p1Choice = characterList.size() - 1;

		p1CurrentCharPic->changeImage(charPicList[p1Choice]);
		p1CurrentCharPic->translate(glm::vec2(Input::SCREEN_WIDTH * 0.25, Input::SCREEN_HEIGHT * 0.52));
		p1CurrentCharPic->scale(glm::vec2(239 / 2, 307 / 2), true);
	}

	if (playerList[1] == nullptr) {

	}
	else {
		if (p2BtnLeft->buttonClick()) {
			p2Choice--;
			if (p2Choice < 0) p2Choice = characterList.size() - 1;
		}
		if (p2BtnRight->buttonClick()) {
			p2Choice++;
			if (p2Choice > characterList.size() - 1) p2Choice = 0;
		}
		//p2CurrentCharPic = charPicList[p2Choice];
		//p2CurrentCharPic->translate(glm::vec2(Input::SCREEN_WIDTH * 0.75, Input::SCREEN_HEIGHT * 0.52));
		//p2CurrentCharPic->scale(glm::vec2(239 / 2, 307 / 2));
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
		p1CurrentCharPic->draw();

		p1CharacterSelected->move(glm::vec2((Input::SCREEN_WIDTH * 0.25)- (p1CharacterSelected->getSize().x / 2), Input::SCREEN_HEIGHT * 0.25));
		p1CharacterSelected->draw(characterList[p1Choice].name, glm::vec4(1.0, 1.0, 1.0, 1.0), 1);

		// Ready Info Text
		p1InfoText->move(glm::vec2((Input::SCREEN_WIDTH * 0.25) - (p1InfoText->getSize().x / 4), Input::SCREEN_HEIGHT * 0.75));
		p1InfoText->scale(glm::vec2(0.5, 0.5));
		p1InfoText->draw("Press [Space] or A to ready!", glm::vec4(1.0, 1.0, 1.0, 1.0), 1);
	}
	else {
		// Player 1 Join Info Text
		p1InfoText->move(glm::vec2((Input::SCREEN_WIDTH * 0.25) - (p1InfoText->getSize().x / 4), Input::SCREEN_HEIGHT * 0.25));
		p1InfoText->scale(glm::vec2(0.5, 0.5));
		p1InfoText->draw("Press [Space] or A to join!", glm::vec4(1.0, 1.0, 1.0, 1.0), 1);
	}

	if (playerList[1] != nullptr) {
		p2BtnLeft->draw();
		p2BtnRight->draw();
		p2CurrentCharPic->draw();
		p2CharacterSelected->move(glm::vec2((Input::SCREEN_WIDTH * 0.75) - (p2CharacterSelected->getSize().x / 2), Input::SCREEN_HEIGHT * 0.25));
		p2CharacterSelected->draw(characterList[p2Choice].name, glm::vec4(1.0, 1.0, 1.0, 1.0), 1);

		// Ready Info Text
		p2InfoText->move(glm::vec2((Input::SCREEN_WIDTH * 0.75) - (p2InfoText->getSize().x / 4), Input::SCREEN_HEIGHT * 0.75));
		p2InfoText->scale(glm::vec2(0.5, 0.5));
		p2InfoText->draw("Press [Enter] or A to ready!", glm::vec4(1.0, 1.0, 1.0, 1.0), 1);
	}
	else {
		// Player 2 Join Info Text
		p2InfoText->move(glm::vec2((Input::SCREEN_WIDTH * 0.75) - (p2InfoText->getSize().x / 4), Input::SCREEN_HEIGHT * 0.25));
		p2InfoText->scale(glm::vec2(0.5, 0.5));
		p2InfoText->draw("Press [Space] or A to join!", glm::vec4(1.0, 1.0, 1.0, 1.0), 1);
	}

	backBtn->draw();
	startBtn->draw();
}