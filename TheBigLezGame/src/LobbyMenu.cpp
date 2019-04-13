#include "LobbyMenu.h"

vector<Player::Character*> GameData::g_PlayerData{ nullptr, nullptr };

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
	BigLez.id = 1;
	BigLez.fileLocation = "assets/Characters/BigLez/lez.dae";
	BigLez.name = "Leslie";
	BigLez.health = 100;
	BigLez.walkSpeed = 10;
	characterList.push_back(BigLez);

	// Picture setup for Player 1
	characterPicSetup("assets/Characters/BigLez/biglezPicture.png", p1CharPicList);

	// Picture setup for Player 2
	characterPicSetup("assets/Characters/BigLez/biglezPicture.png", p2CharPicList);


	// Create Sassy
	Player::Character Sassy;
	Sassy.id = 2;
	Sassy.fileLocation = "assets/Characters/Sassy/sassy.dae";
	Sassy.name = "Sassy";
	Sassy.health = 100;
	Sassy.walkSpeed = 10;
	characterList.push_back(Sassy);

	// Picture setup for Player 1
	characterPicSetup("assets/Characters/Sassy/sassyPicture.png", p1CharPicList);

	// Picture setup for Player 2
	characterPicSetup("assets/Characters/Sassy/sassyPicture.png", p2CharPicList);


	// Create Donny
	Player::Character Donny;
	Donny.id = 3;
	Donny.fileLocation = "assets/Characters/Donny/donny.dae";
	Donny.name = "Donny";
	Donny.health = 100;
	Donny.walkSpeed = 10;
	characterList.push_back(Donny);

	// Picture setup for Player 1
	characterPicSetup("assets/Characters/Donny/donnyPicture.png", p1CharPicList);

	// Picture setup for Player 2
	characterPicSetup("assets/Characters/Donny/donnyPicture.png", p2CharPicList);


	// Create Clarence
	Player::Character Clarence; 
	Clarence.id = 4;
	Clarence.fileLocation = "assets/Characters/Clarence/Clarence.dae";
	Clarence.name = "Clarence";
	Clarence.health = 100000;
	Clarence.walkSpeed = 12;
	Clarence.isLocked = true;
	characterList.push_back(Clarence);

	// Picture setup for Player 1
	characterPicSetup("assets/Characters/Clarence/clarencePicture.png", p1CharPicList);

	// Picture setup for Player 2
	characterPicSetup("assets/Characters/Clarence/clarencePicture.png", p2CharPicList);
}

// For adding images to character picture lists
void LobbyMenu::characterPicSetup(const char* filename, vector<Image*>& piclist)
{
	Image* t_picture = new Image(filename, glm::vec2(0, 0));
	piclist.push_back(t_picture);
}

// Returns colour depending on the player status
glm::vec4 LobbyMenu::colourCheck(bool ready)
{
	if (ready) return glm::vec4(0.0f, 0.9f, 0.0f, 1.0f); // Green
	else return glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // White
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
	fog = new Image("assets/Art/fog.png", glm::vec2(640.0f, 0.0f));

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
	timerText = new Text(glm::vec2(Input::SCREEN_WIDTH * 0.50, Input::SCREEN_HEIGHT * 0.50 - 20), "assets/Fonts/ariali.ttf");
	timerText->scale(glm::vec2(1.4, 1.4));
	selectedMenu = menu;
}

void LobbyMenu::update() 
{
	// Fog Scrolling
	fog->translate(glm::vec2(fogPos, 360));
	fog->scale(glm::vec2(3840.0f, 1080.0f), true);
	fogPos += 4;
	if (fogPos > 3800) fogPos = 0;

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

	// Player 1 Character Selection
	if (playerList[0] != nullptr) {

		if (!p1Ready) {
			// Left Character Select Button
			if (p1BtnLeft->buttonClick()) {
				p1Choice--;
				if (p1Choice < 0) p1Choice = characterList.size() - 1;
			}

			// Right Character Select Button
			if (p1BtnRight->buttonClick()) {
				p1Choice++;
				if (p1Choice > characterList.size() - 1) p1Choice = 0;
			}
			if (p1Choice < 0) p1Choice = characterList.size() - 1;

			// Confirm Character Selection Key
			int confirmKey;
			if (playerList[0]->control == Input::KEYBOARD) confirmKey = GLFW_KEY_ENTER;
			else if (playerList[0]->control == Input::CONTROLLER1 || playerList[0]->control == Input::CONTROLLER2) confirmKey = 2;
			if (Input::determineInput(playerList[0]->control, confirmKey)) {
				p1Ready = true;
				playerList[0]->id = characterList[p1Choice].id;
				playerList[0]->name = characterList[p1Choice].name;
				playerList[0]->fileLocation = characterList[p1Choice].fileLocation;
				playerList[0]->health = characterList[p1Choice].health;
				playerList[0]->walkSpeed = characterList[p1Choice].walkSpeed;
			}
		}
		else {
			// Cancel Character Selection
			int cancelKey;
			if (playerList[0]->control == Input::KEYBOARD) cancelKey = GLFW_KEY_BACKSPACE;
			else if (playerList[0]->control == Input::CONTROLLER1 || playerList[0]->control == Input::CONTROLLER2) cancelKey = 1;
			if (Input::determineInput(playerList[0]->control, cancelKey)) {
				p1Ready = false;
			}
		}

		// Update Character Picture
		p1CurrentCharPic = p1CharPicList[p1Choice];
		p1CurrentCharPic->translate(glm::vec2(Input::SCREEN_WIDTH * 0.25, Input::SCREEN_HEIGHT * 0.52));
		p1CurrentCharPic->scale(glm::vec2(239 / 2, 307 / 2), true);
	}

	// Player 2 Character Selection
	if (playerList[1] != nullptr) {

		if (!p2Ready) {
			// Left Character Select Button
			if (p2BtnLeft->buttonClick()) {
				p2Choice--;
				if (p2Choice < 0) p2Choice = characterList.size() - 1;
			}

			// Right Character Select Button
			if (p2BtnRight->buttonClick()) {
				p2Choice++;
				if (p2Choice > characterList.size() - 1) p2Choice = 0;
			}

			// Confirm Character Selection
			int confirmKey;
			if (playerList[1]->control == Input::KEYBOARD) confirmKey = GLFW_KEY_ENTER;
			else if (playerList[1]->control == Input::CONTROLLER1 || playerList[1]->control == Input::CONTROLLER2) confirmKey = 2;
			if (Input::determineInput(playerList[1]->control, confirmKey)) {
				p2Ready = true;
				playerList[1]->id = characterList[p2Choice].id;
				playerList[1]->name = characterList[p2Choice].name;
				playerList[1]->fileLocation = characterList[p2Choice].fileLocation;
				playerList[1]->health = characterList[p2Choice].health;
				playerList[1]->walkSpeed = characterList[p2Choice].walkSpeed;
			}
		}
		else {
			// Cancel Character Selection
			int cancelKey;
			if (playerList[1]->control == Input::KEYBOARD) cancelKey = GLFW_KEY_BACKSPACE;
			else if (playerList[1]->control == Input::CONTROLLER1 || playerList[1]->control == Input::CONTROLLER2) cancelKey = 1;
			if (Input::determineInput(playerList[1]->control, cancelKey)) {
				p2Ready = false;
			}
		}

		// Update Character Picture
		p2CurrentCharPic = p2CharPicList[p2Choice];
		p2CurrentCharPic->translate(glm::vec2(Input::SCREEN_WIDTH * 0.75, Input::SCREEN_HEIGHT * 0.52));
		p2CurrentCharPic->scale(glm::vec2(239 / 2, 307 / 2), true);
	}

	// If both players are ready, start the timer
	if (p1Ready && p2Ready || p1Ready && playerList[1] == nullptr) {
		if (!gameTimerStart) {
			gameTimerStart = true;
			startTime = glfwGetTime();
		}
		timeOnTimer = 10 - (glfwGetTime() - startTime);
		if (gameTimerStart && timeOnTimer <= 0) {
			// Start the game
			GameData::g_PlayerData = playerList;
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			selectedMenu->setCurrent(selectedMenu->getGameScreen());
			selectedMenu->getCurrentState()->handle(selectedMenu);
		}
	}
	else {
		gameTimerStart = false;
	}

	// Back to previous menu
	if (backBtn->buttonClick()) {
		selectedMenu->setCurrent(selectedMenu->getMainMenu());
		selectedMenu->getCurrentState()->handle(selectedMenu);
	}

	//if (startBtn->buttonClick()) {
	//	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//	selectedMenu->setCurrent(selectedMenu->getSinglePlayer());
	//	selectedMenu->getCurrentState()->handle(selectedMenu);
	//}
}

void LobbyMenu::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	background->draw();
	fog->draw();

	if (playerList[0] != nullptr) {
		if (!p1Ready) {
			p1BtnLeft->draw();
			p1BtnRight->draw();

			// Ready Info Text
			p1InfoText->move(glm::vec2((Input::SCREEN_WIDTH * 0.25) - (p1InfoText->getSize().x / 4), Input::SCREEN_HEIGHT * 0.75));
			p1InfoText->scale(glm::vec2(0.5, 0.5));
			p1InfoText->draw("Press [Space] or X to ready!", glm::vec4(1.0, 1.0, 1.0, 1.0), 1);
		}
		else {
			// Ready Text
			p1InfoText->move(glm::vec2((Input::SCREEN_WIDTH * 0.25) - (p1InfoText->getSize().x / 4), Input::SCREEN_HEIGHT * 0.75));
			p1InfoText->scale(glm::vec2(0.7, 0.7));
			p1InfoText->draw("Ready!", glm::vec4(0.0, 1.0, 0.0, 1.0), 1);
		}

		// Draw player 1s currently selected character picture
		p1CurrentCharPic->draw();
		p1CharacterSelected->move(glm::vec2((Input::SCREEN_WIDTH * 0.25)- (p1CharacterSelected->getSize().x / 2), Input::SCREEN_HEIGHT * 0.25));
		p1CharacterSelected->draw(characterList[p1Choice].name, glm::vec4(1.0, 1.0, 1.0, 1.0), 1);
	}
	else {
		// Player 1 Join Info Text
		p1InfoText->move(glm::vec2((Input::SCREEN_WIDTH * 0.25) - (p1InfoText->getSize().x / 4), Input::SCREEN_HEIGHT * 0.25));
		p1InfoText->scale(glm::vec2(0.5, 0.5));
		p1InfoText->draw("Press [Space] or A to join!", glm::vec4(1.0, 1.0, 1.0, 1.0), 1);
	}

	if (playerList[1] != nullptr) {
		if (!p2Ready) {
			p2BtnLeft->draw();
			p2BtnRight->draw();

			// Ready Info Text
			p2InfoText->move(glm::vec2((Input::SCREEN_WIDTH * 0.75) - (p2InfoText->getSize().x / 4), Input::SCREEN_HEIGHT * 0.75));
			p2InfoText->scale(glm::vec2(0.5, 0.5));
			p2InfoText->draw("Press [Enter] or X to ready!", glm::vec4(1.0, 1.0, 1.0, 1.0), 1);
		}
		else {
			p2InfoText->move(glm::vec2((Input::SCREEN_WIDTH * 0.75) - (p2InfoText->getSize().x / 4), Input::SCREEN_HEIGHT * 0.75));
			p2InfoText->scale(glm::vec2(0.7, 0.7));
			p2InfoText->draw("Ready!", glm::vec4(0.0, 1.0, 0.0, 1.0), 1);
		}

		// Draw player 2s currently selected character picture
		p2CurrentCharPic->draw();
		p2CharacterSelected->move(glm::vec2((Input::SCREEN_WIDTH * 0.75) - (p2CharacterSelected->getSize().x / 2), Input::SCREEN_HEIGHT * 0.25));
		p2CharacterSelected->draw(characterList[p2Choice].name, glm::vec4(1.0, 1.0, 1.0, 1.0), 1);

	}
	else {
		// Player 2 Join Info Text
		p2InfoText->move(glm::vec2((Input::SCREEN_WIDTH * 0.75) - (p2InfoText->getSize().x / 4), Input::SCREEN_HEIGHT * 0.25));
		p2InfoText->scale(glm::vec2(0.5, 0.5));
		p2InfoText->draw("Press [Space] or A to join!", glm::vec4(1.0, 1.0, 1.0, 1.0), 1);
	}

	// Draw countdown
	if (gameTimerStart) {
		timerText->draw(std::to_string(timeOnTimer), glm::vec4(1.0, 1.0, 1.0, 1.0), 1);
	}

	backBtn->draw();
	//startBtn->draw();
}