#include "Gun.h"

Gun::Gun(const char * filename, std::string gunName, GLuint maxAmmo, GLuint clipSize) : Weapon(filename, glm::vec3(0.0f, 0.0f, 0.0f)),
		m_gunName(gunName), m_maxAmmo(maxAmmo), m_clipSize(clipSize)
{
	
}

Gun::~Gun()
{

}

void Gun::update()
{

}
