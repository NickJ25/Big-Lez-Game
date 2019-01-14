#include "Button.h"

Button::Button(glm::vec2 position, std::string button_text) //, MenuState * destination
{
	m_texNormal = new Image("assets/Art/button-normal.png", position);
	m_texNormal->scale(glm::vec2(0.24f, 0.15f));
	m_texHover = new Image("assets/Art/button-hover.png", position);
	m_texHover->scale(glm::vec2(0.24f, 0.15f));
	m_texClick = new Image("assets/Art/button-click.png", position);
	m_texClick->scale(glm::vec2(0.24f, 0.15f));
	//m_buttonCollision->centre = position;
	//m_buttonCollision->height = 120;
	//m_buttonCollision->width = 120;

}

Button::~Button()
{

}

void Button::update(glm::vec2* mousePos)
{

}

void Button::draw()
{
	m_texNormal->draw();
}
