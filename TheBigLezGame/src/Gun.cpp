#include "Gun.h"

Gun::Gun(const char * filename, std::string gunName, GLuint maxAmmo, GLuint clipSize, float shootDelay, bool allowSpray) : Weapon(filename, glm::vec3(0.0f, 0.0f, 0.0f)),
		m_gunName(gunName), m_maxAmmo(maxAmmo), m_clipSize(clipSize), sprayAllowed(allowSpray), m_shootDelay(shootDelay)
{
	t_ammoCount = new Text(glm::vec2(50.0, 80.0), "assets/Fonts/Another_.ttf");
	t_gunName = new Text(glm::vec2(50.0, 40.0), "assets/Fonts/Another_.ttf");
	i_crosshair = new Image("assets/Art/crosshair.png", glm::vec2(Input::SCREEN_WIDTH / 2, Input::SCREEN_HEIGHT / 2), 16, 16, false);
	i_crosshair->scale(glm::vec2(16, 16), false);
}

Gun::~Gun()
{

}

void Gun::shoot(bool clicked)
{
	if (sprayAllowed) {
		if (lastFired + m_shootDelay < glfwGetTime()) {
			if (m_currentClip > 0) {
				m_currentClip--;
				lastFired = glfwGetTime();
			}
		}
	}
	else {

		if (clicked == true && !gunFired) {
			if (lastFired + m_shootDelay < glfwGetTime()) {
				if (m_currentClip > 0) {
					m_currentClip--;
					gunFired = true;
					lastFired = glfwGetTime();
				}
			}
		}
		else if (clicked == false) {
			gunFired = false;
		}
	}
}

void Gun::reload(bool clicked)
{
	if (clicked) {
		if (m_currentClip != m_clipSize) {
			m_currentClip = m_clipSize;
		}
	}
}

void Gun::setMatrix(glm::mat4 newMat)
{
	GameObject::setMatrix(newMat);
}

void Gun::update()
{
	t_ammoCount->draw(std::to_string(m_currentClip) + " / " + std::to_string(m_clipSize), glm::vec4(1.0, 1.0, 1.0, 1.0),1);
	t_gunName->draw(m_gunName, glm::vec4(1.0, 1.0, 1.0, 1.0),1);
	i_crosshair->draw();
}

void Gun::checkHit()
{

}

void Gun::primaryMove(bool active)
{
	shoot(active);
}

void Gun::secondaryMove(bool active)
{

}

void Gun::action(bool active)
{
	reload(active);
}

bool Gun::hasAttacked()
{
	if (sprayAllowed) {
		return gunFired;
	}
	else {
		if (gunFired && !alreadyFired) {
			alreadyFired = true;
			return gunFired;
		}
		else if(!gunFired) {
			alreadyFired = false;
			return false;
		}
		else {
			return false;
		}
	}
}
