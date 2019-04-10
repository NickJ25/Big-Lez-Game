#pragma once
#include "MenuState.h"
#include "Menu.h"
#include "Button.h"
#include "Image.h"
#include "Text.h"
#include "Player.h"
#include "windowGLFW.h"
#include <vector>

class LobbyMenu : public MenuState {
private:
	Image* background, *fog;
	float fogPos = 0;

	Image* p1CurrentCharPic = nullptr, *p2CurrentCharPic = nullptr;
	Button* backBtn, *startBtn;
	GLFWwindow* m_window;
	Button* p1BtnLeft, *p1BtnRight;
	Button* p2BtnLeft, *p2BtnRight;
	Text* p1CharacterSelected, *p2CharacterSelected;
	Text* p1InfoText, *p2InfoText;
	Text* p1Status, *p2Status;
	int p1Choice = 0, p2Choice = 0;
	bool p1Ready = false , p2Ready = false;

	bool keyboardInUse = false;
	bool controller1InUse = false;
	bool controller2InUse = false;
	vector<Player::Character*> playerList{ nullptr, nullptr };
	vector<Player::Character> characterList;
	vector<Image*>p1CharPicList;
	vector<Image*>p2CharPicList;
	void addController(Input::ControllerType controller);
	void addCharacters();
	void characterPicSetup(const char* filename, vector<Image*> &piclist);
	glm::vec4 colourCheck(bool ready);

public:
	LobbyMenu();
	virtual ~LobbyMenu() {};
	void handle(Menu* menu);
	void update();
	void draw();
};