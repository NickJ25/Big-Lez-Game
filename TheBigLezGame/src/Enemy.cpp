#include "Enemy.h"

Enemy::Enemy(Character character) : GameObject(character.fileLocation.c_str())
{
	inside = false;
	outsideMovement = false;
	paused = false;
	Jump = false;
	moving = true;
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
	angularVelocity = 0.5f;
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
	//cout << getPosition().x << " , " << getPosition().z << endl;
	glm::vec3 current;
	glm::vec3 next;
	glm::vec3 distanceToBeCovered;
	glm::vec3 movementStep;
	bool rotated = false;
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
			glm::mat4 test = getMatrix();


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
				outerPath.pop_back();
				rotated = false;
			}
		}
		else {
			if (outsideMovement == true && Jump == false) {

				inside = true;
				//jumping animation
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
	//cout << "choomah position = " << getPosition().x << " , " << getPosition().y << " , " << getPosition().z << " ) " << endl;

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

