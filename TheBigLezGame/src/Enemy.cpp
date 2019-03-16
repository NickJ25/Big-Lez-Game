#include "Enemy.h"

Enemy::Enemy(Character character) : GameObject(character.fileLocation.c_str())
{
	inside = false;
	outsideMovement = false;
	paused = false;
	Jump = false;
	jumpingCounter = 0;

	if (character.name == "charger") {
		velocity = 0.095f;
	}

	if (character.name == "normal") {
		velocity = 0.05f;
	}

	if (character.name == "brawler") {
		velocity = 0.02f;
	}
	angularVelocity = 0.005f;
	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
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
			rotation = glm::normalize(distanceToBeCovered); // rotation we want to be at
			glm::vec3 currentRot = getRotation(); // current rotation


			if (std::round(currentRot.x) != std::round(rotation.x) || std::round(currentRot.y) != std::round(rotation.y) || std::round(currentRot.z) != std::round(rotation.z))
			{

				////calculate angle between the two vectors
				//float angle = glm::acos(glm::dot(currentRot, rotation));
				//glm::mat4 tempMat(1.0f);
				//tempMat = glm::translate(tempMat, getPosition());
				//tempMat = glm::rotate(tempMat, angle, glm::vec3(0.0, 1.0, 0.0));
				//setMatrix(tempMat);
				
			}

			movementStep = glm::normalize(distanceToBeCovered) * velocity;
			Move(glm::vec3(movementStep));

			
			if (glm::vec3(std::round(getPosition().x), -12.5f, std::round(getPosition().z)) == next)
			{
				outerPath.pop_back();
			}
		}
		else {
			if (outsideMovement == true && Jump == false) {

				inside = true;
				//jumping animation
				setAnimation(4.58f, 1.0f);
				velocity = 0.05;

				//get to the second of the pair 
				current = getPosition();
				next = getOuterPathEnd().second;
				distanceToBeCovered = next - current;
				movementStep = glm::normalize(distanceToBeCovered) * velocity;
				Move(glm::vec3(movementStep));

				if (glm::vec3(std::round(getPosition().x), -12.5f, std::round(getPosition().z)) == next)
				{
					cout << endl;
					Jump = true;
				}
				cout << endl;
			}

		}

		if (outsideMovement == true && outerPath.empty() == true && innerPath.empty() == false && Jump == true)
		{

			//running animation
			setAnimation(0.0f, 8.3f);
			velocity = 0.05;
				
			//enemy has reached a window
			setInnerPathEnd(target->getPosition());

			current = getPosition();
			next = innerPath.back();


			//get angle between the current and the next node
			distanceToBeCovered = next - current;
			movementStep = glm::normalize(distanceToBeCovered) * velocity;
			Move(glm::vec3(movementStep));

			if (glm::vec3(std::round(getPosition().x), -12.5f, std::round(getPosition().z)) == next)
			{
				innerPath.pop_back();
			}
		}
	}
	cout << "choomah position = " << getPosition().x << " , " << getPosition().y << " , " << getPosition().z << " ) " << endl;

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

