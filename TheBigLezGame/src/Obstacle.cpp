#include "Obstacle.h"

Obstacle::Obstacle(Character character, std::string n, glm::vec3 startPos) : GameObject(startPos, character.file.c_str())
{
	name = n;
	m_char = character;

}

Obstacle::Obstacle( std::string n, glm::vec3 startPos) : GameObject(startPos)
{
	name = n;
}

Obstacle::~Obstacle()
{
}



void Obstacle::update()
{

}
