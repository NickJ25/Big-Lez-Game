#include "Button.h"

Button::Button(glm::vec2 position, std::string button_text) //, MenuState * destination
{
	m_position = position;
	
	// Button Art
	m_texNormal = new Image("assets/Art/button-normal.png", position);
	m_texNormal->scale(glm::vec2(0.24f, 0.15f));
	m_texHover = new Image("assets/Art/button-hover.png", position);
	m_texHover->scale(glm::vec2(0.24f, 0.15f));
	m_texClick = new Image("assets/Art/button-click.png", position);
	m_texClick->scale(glm::vec2(0.24f, 0.15f));

	m_currentImage = m_texNormal;

	// Button Text
	m_textBox = new Text(position, "assets/Fonts/Another_.ttf");
	m_text = button_text;

	// Button Collision Box
	m_buttonCollision = new AABB();
	m_buttonCollision->centre = position;
	m_buttonCollision->height = 55;
	m_buttonCollision->width = 150;

	// Click State
	m_buttonClick = false;
}

Button::~Button()
{

}

// Returns true if the button has been pressed.
bool Button::buttonClick()
{
	// Check if the button is within the button's collision box.
	if (abs(m_buttonCollision->centre.x - Input::mouse1.current_Xpos) > (m_buttonCollision->width)) return false;
	if (abs(m_buttonCollision->centre.y - Input::mouse1.current_Ypos) > (m_buttonCollision->height)) return false;
	m_currentImage = m_texHover;
	if (Input::mouse1.buttons[GLFW_MOUSE_BUTTON_LEFT]) {
		m_buttonClick = true;
		m_currentImage = m_texClick;
	}
	if (!Input::mouse1.buttons[GLFW_MOUSE_BUTTON_LEFT] && m_buttonClick) {
		m_buttonClick = false;
		return true;
	}
	else {
		return false;
	}
}

void Button::draw()
{
	m_currentImage->draw();
	m_textBox->move(glm::vec2(m_position.x - (m_textBox->getSize().x / 2), m_position.y - (m_textBox->getSize().y / 2) - 12));
	m_textBox->draw(m_text, glm::vec3(1.0, 1.0, 1.0));
	m_currentImage = m_texNormal;
	
}
