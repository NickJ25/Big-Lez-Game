#include "Enemy.h"
#include "PathManager.h"

Enemy::Enemy(Character character) : GameObject(character.fileLocation.c_str())
{
	//record the characters name
	name = character.name;

	//initialise all the movement variables
	firstPosition = true;
	inside = false;
	outsideMovement = false;
	paused = false;
	Jump = false;
	moving = true;
	jumpingCounter = 0;


	//set physics depending on the character
	if (character.name == "charger") {
		velocity = 0.095f;
		originalVelocity = 0.095;
	}

	if (character.name == "normal") {
		velocity = 0.05f;
		originalVelocity = 0.05;
	}

	if (character.name == "brawler") {
		velocity = 0.07f;
		originalVelocity = 0.02f;
	}

	//constant angular velocity and orientation
	angularVelocity = 0.5f;
	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
}

Enemy::~Enemy()
{
}

void Enemy::setPaused(bool p)
{
	paused = p;
}

bool Enemy::getPaused()
{
	return paused;
}

void Enemy::reset(PathManager* pathmanager)
{
	//resets all the variables to how they weree at spawn, re-adds the object to the path manager to prevent bugs with random spawning
	//setPosition(spawnPoint);
	glm::mat4 tmp(1.0f);
	tmp = glm::translate(tmp, spawnPoint);
	setMatrix(tmp);
	velocity = originalVelocity;
	pathmanager->addToQueue(this);
	inside = false;
	outsideMovement = false;
	paused = false;
	Jump = false;
	moving = true;
	jumpingCounter = 0;
	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Enemy::update()
{
	//uncomment for debugging
	//cout << getPosition().x << " , " << getPosition().z << endl;

	//initialise movement vectors
	glm::vec3 current;
	glm::vec3 next;
	glm::vec3 distanceToBeCovered;
	glm::vec3 movementStep;

	bool rotated = false;

	//if the game isnt paused
	if (paused == false) {

		//if the enemy is currently outside
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

			//calculate angle between the two vectors
			float angle = -glm::acos(glm::dot(currentRot, rotation));
			movementStep = glm::normalize(distanceToBeCovered) * velocity;

				
			//reset the rotation
			glm::mat4 tempMat(1.0f);

			//calculate the translation 
			tempMat = glm::translate(tempMat, getPosition());
			tempMat = glm::translate(tempMat, movementStep);

			if (std::round(currentRot.x) != std::round(rotation.x) || std::round(currentRot.z) != std::round(rotation.z) && rotated == false)
			{
				//reapply the rotation
				tempMat = glm::rotate(tempMat, angle, glm::vec3(0.0f, 1.0f, 0.0f));
				rotated = true;
			}

			//set the matrix
			setMatrix(tempMat);

			//move the bounding box with the model without applying rotation
			if (getCollider())
				getCollider()->setCollider(tempMat[3]);

				glm::vec3 check = getRotation();
			if (glm::vec3(std::round(getPosition().x), -12.5f, std::round(getPosition().z)) == next)
			{
				//remove this from the vector and set it back to unrotated
				outerPath.pop_back();
				rotated = false;
			}
		}
		else {
			if (outsideMovement == true && Jump == false) {

				inside = true;
				//jumping animation
				if (name == "brawler")
					setAnimValues(0.0f, 1.0f);
				else
					setAnimValues(4.58, 1.0f);

				velocity = 0.1;

				//get to the second of the pair 
				current = getPosition();

				next = getOuterPathEnd().second;
				distanceToBeCovered = next - current;

				glm::vec3 jumpDirection = glm::normalize(getOuterPathEnd().second - getPosition());
				rotation = glm::normalize(jumpDirection); // rotation we want to be at
				glm::vec3 currentRot = getRotation(); // current rotation

				//calculate angle between the two vectors
				float angle = -glm::acos(glm::dot(currentRot, rotation));
				movementStep = glm::normalize(distanceToBeCovered) * velocity;


				//reset the rotation
				glm::mat4 tempMat(1.0f);

				//calculate the translation 
				tempMat = glm::translate(tempMat, getPosition());
				tempMat = glm::translate(tempMat, movementStep);

				if (std::round(currentRot.x) != std::round(rotation.x) || std::round(currentRot.y) != std::round(rotation.y) || std::round(currentRot.z) != std::round(rotation.z))
				{
					//reapply the rotation
					tempMat = glm::rotate(tempMat, angle, glm::vec3(0.0f, 1.0f, 0.0f));
				}

				//set the matrix
				setMatrix(tempMat);

				//move the bounding box with the model without applying rotation
				if (getCollider())
					getCollider()->setCollider(tempMat[3]);

				if (glm::vec3(std::round(getPosition().x), -12.5f, std::round(getPosition().z)) == next)
				{
					Jump = true;
				}
				cout << endl;
			}

		}

		if (outsideMovement == true && outerPath.empty() == true && innerPath.empty() == false && Jump == true)
		{

			//running animation
			setAnimValues(0.0f, 8.3f);

			velocity = 0.05;
				
			//enemy has reached a window
			setInnerPathEnd(target->getPosition());

			current = getPosition();
			next = innerPath.back();


			//get angle between the current and the next node
			distanceToBeCovered = next - current;
			movementStep = glm::normalize(distanceToBeCovered) * velocity;

			rotation = glm::normalize(distanceToBeCovered); // rotation we want to be at
			glm::vec3 currentRot = getRotation(); // current rotation

			//calculate angle between the two vectors
			float angle = -glm::acos(glm::dot(currentRot, rotation));

			//reset the rotation
			glm::mat4 tempMat(1.0f);

			//calculate the translation 
			tempMat = glm::translate(tempMat, getPosition());

			//if not touching a player
			if(moving == true)
			tempMat = glm::translate(tempMat, movementStep);

			if (std::round(currentRot.x) != std::round(rotation.x) || std::round(currentRot.y) != std::round(rotation.y) || std::round(currentRot.z) != std::round(rotation.z))
			{
				//reapply the rotation
				tempMat = glm::rotate(tempMat, angle, glm::vec3(0.0f, 1.0f, 0.0f));
			}

			//set the matrix
			setMatrix(tempMat);

			//move the bounding box with the model without applying rotation
			if (getCollider())
				getCollider()->setCollider(tempMat[3]);

			if (glm::vec3(std::round(getPosition().x), -12.5f, std::round(getPosition().z)) == next)
			{
				innerPath.pop_back();
			}
		}
	}
}

void Enemy::setPathEnd(std::pair<glm::vec3, glm::vec3> p)
{
	outerPathEnd = p;
}

void Enemy::setInnerPathEnd(glm::vec3 p)
{
	innerPathEnd = p;
}

std::pair<glm::vec3, glm::vec3> Enemy::getOuterPathEnd()
{
	return outerPathEnd;
}

glm::vec3 Enemy::getInnerPathEnd()
{
	return innerPathEnd;
}

glm::vec3 Enemy::getCurrentTargetPosition()
{
	return currentTargetPosition;
}

void Enemy::setCurrentTargetPosition(glm::vec3 p)
{
	currentTargetPosition = p;
}

bool Enemy::getJump()
{
	return Jump;
}

void Enemy::setAnimValues(float s, float e)
{
	animStart = s;
	animEnd = e;
	setAnimation(s, e);
}

void Enemy::setSpawnPoint(glm::vec3 p)
{
	spawnPoint = p;
}

bool Enemy::getLocation()
{
	return inside;
}

void Enemy::setMoving(bool newMove)
{
	moving = newMove;
}

void Enemy::setTarget(Player* p)
{
	target = p;
}

Player* Enemy::getTarget()
{
	return target;
}

std::vector<glm::vec3> Enemy::getPath()
{
	return outerPath;
}

void Enemy::setPath(std::vector<glm::vec3> p, bool outer)
{
	if (outer == true) {
		outerPath = p;
		originalOuterPath = p;
	}
	else
		innerPath = p;
}

