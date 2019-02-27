#pragma once

class Menu;

class MenuState
{
protected:
	Menu* selectedMenu;
public:
	virtual ~MenuState() {};
	virtual void handle(Menu* menu) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	
};