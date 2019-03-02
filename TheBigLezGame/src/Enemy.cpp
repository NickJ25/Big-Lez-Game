#include "Enemy.h"

Enemy::Enemy(Character character) : GameObject(character.fileLocation.c_str())
{

	velocity = 0.05f;
}

Enemy::~Enemy()
{
}

float dot(glm::vec3 a, glm::vec3 b)  //calculates dot product of a and b
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float mag(glm::vec3 a)  //calculates magnitude of a
{
	return std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

void Enemy::update()
{
	//get it to follow
	if (!outerPath.empty())
	{
		glm::vec3 current = getPosition();
		glm::vec3 next = outerPath.back();
		
		//get angle between the current and the next node
	//	float angle = std::acos(dot(current, next) / (mag(current)*mag(next)));
		glm::vec3 distanceToBeCovered = next - current;
		glm::vec3 movementStep = glm::normalize(distanceToBeCovered) * velocity;
	//	float dx = (double)(cos(angle) * velocity);
	//	float dy = (double)(sin(angle) * velocity);

		Move(movementStep);
		cout << std::round(getPosition().x) << std::round(getPosition().z) << endl;
		if (glm::vec3(std::round(getPosition().x), std::round(getPosition().y), std::round(getPosition().z)) == next )
		{
			//current = next;
			outerPath.pop_back();
		}

	}
}

std::vector<glm::vec3> Enemy::getPath()
{
	return outerPath;
}

void Enemy::setPath(std::vector<glm::vec3> p, bool outer)
{
	if (outer == true)
		outerPath = p;
	else
		innerPath = p;
}

void Enemy::setPathEnd(glm::vec3 p, bool outer)
{
	if (outer == true)
		outerPathEnd = p;
	else
		innerPathEnd = p;
}

