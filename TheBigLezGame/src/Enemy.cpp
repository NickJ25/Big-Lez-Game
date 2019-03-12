#include "Enemy.h"

Enemy::Enemy(Character character) : GameObject(character.fileLocation.c_str())
{
	inside = false;
	outsideMovement = false;
	paused = false;
	setJump = false;
	jumpingCounter = 0;

	velocity = 0.05f;

	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
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
void Enemy::setPaused(bool p)
{
	paused = p;
}

bool Enemy::getPaused()
{
	return paused;
}

void Enemy::update()
{
	glm::vec3 current;
	glm::vec3 next;
	glm::vec3 distanceToBeCovered;
	glm::vec3 movementStep;
	if (paused == false) {
		//get it to follow
		if (!outerPath.empty())
		{
			inside = false;
			if (outsideMovement == false)
				outsideMovement = true;

			current = getPosition();
			next = outerPath.back();

			//get angle between the current and the next node
			distanceToBeCovered = next - current;
			rotation = distanceToBeCovered;
			movementStep = glm::normalize(distanceToBeCovered) * velocity;

			Move(glm::vec3(movementStep));
			//cout << std::round(getPosition().x) << std::round(getPosition().y) << std::round(getPosition().z) << endl;
			if (glm::vec3(std::round(getPosition().x), -12.5f, std::round(getPosition().z)) == next)
			{
				outerPath.pop_back();
			}
		}
		else {
			if (outsideMovement == true)
				inside = true;

			if (setJump == false) {
				//set animation to jumping 
				jumpingCounter = 2;
				setJump = true;
			}
		}

		if (outsideMovement == true && outerPath.empty() == true && innerPath.empty() == false)
		{

			if (jumpingCounter > 0)
			{
				//jumping animation
				setAnimation(4.58f, 1.0f);
				velocity = 0.1;
			}
			else
			{
				//running animation
				setAnimation(0.0f, 8.3f);
				velocity = 0.05;
				
			}
			//enemy has reached a window
			setPathEnd(target->getPosition(), false);
			current = getPosition();
			next = innerPath.back();

			//get angle between the current and the next node
			distanceToBeCovered = next - current;
			rotation = distanceToBeCovered;
			movementStep = glm::normalize(distanceToBeCovered) * velocity;

			Move(glm::vec3(movementStep));

			if (glm::vec3(std::round(getPosition().x), -12.5f, std::round(getPosition().z)) == next)
			{
				innerPath.pop_back();
				jumpingCounter = 0;
			}
			//get him to jump then calculate new path with new grid to nearest player

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
