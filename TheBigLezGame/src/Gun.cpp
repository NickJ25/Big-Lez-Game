#include "Gun.h"

Gun::Gun(const char * filename, std::string gunName, GLuint maxAmmo, GLuint clipSize) : Weapon(filename, glm::vec3(0.0f, 0.0f, 0.0f)),
		m_gunName(gunName), m_maxAmmo(maxAmmo), m_clipSize(clipSize)
{
	t_ammoCount = new Text(glm::vec2(50.0, 80.0), "assets/Fonts/Another_.ttf");
	t_gunName = new Text(glm::vec2(50.0, 40.0), "assets/Fonts/Another_.ttf");
}

Gun::~Gun()
{

}

void Gun::shoot()
{
	if (m_currentClip >= 0) {
		m_currentClip--;
	}
}

void Gun::reload()
{
	if (m_currentClip != m_clipSize) {
		m_currentClip = m_clipSize;
	}
}

void Gun::setMatrix(glm::mat4 newMat)
{
	GameObject::setMatrix(newMat);
}

void Gun::update()
{
	t_ammoCount->draw(std::to_string(m_currentClip) + " / " + std::to_string(m_clipSize), glm::vec3(1.0, 1.0, 1.0));
	t_gunName->draw(m_gunName, glm::vec3(1.0, 1.0, 1.0));
}

void Gun::primaryMove()
{
	shoot();
}

void Gun::secondaryMove()
{

}

void Gun::action()
{
	reload();
}
