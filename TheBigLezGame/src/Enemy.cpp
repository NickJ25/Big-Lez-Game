#include "Enemy.h"

Enemy::Enemy(Character character, glm::vec3 startPos) : GameObject(startPos, character.fileLocation.c_str())
{


}

Enemy::~Enemy()
{
}

void Enemy::update()
{
}