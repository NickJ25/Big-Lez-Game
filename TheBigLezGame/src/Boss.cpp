#include "Boss.h"

Boss::Boss(Character character) : GameObject(character.fileLocation.c_str())
{
	paused = false;
	velocity = 0.04;
	angularVelocity = 0.005f;
	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	
	//add potential paths to vector
	//create temporary vector
	std::vector<glm::vec3> tmpPath;
	//fill it
	tmpPath.push_back(glm::vec3(50.0f , -12.5f, -110.0f));
	tmpPath.push_back(glm::vec3(155.0f, -12.5f, -145.0f));
	tmpPath.push_back(glm::vec3(155.0f, -12.5f, -220.0f));
	//add it to the paths
	outerPath.push_back(tmpPath);
	//add end position to same relative position as its path
	outerPathEnd.push_back(glm::vec3(45.0f, -12.5f, -80.0f));
	//and the same with the start position
	spawnPoints.push_back(glm::vec3(-215.0f, -12.5f, -240.0f));

	//reseed then pick a random path for the boss to take
	srand(time(0));
	int randomNumber = (rand() % outerPath.size());
	selectedPath = outerPath.at(randomNumber);
	selectedPathEnd = outerPathEnd.at(randomNumber);
	selectedSpawnPoint = spawnPoints.at(randomNumber);

}

Boss::~Boss()
{
}

void Boss::setPaused(bool p)
{
	paused = p;
}

bool Boss::getPaused()
{
	return paused;
}

void Boss::update()
{
	glm::vec3 current;
	glm::vec3 next;
	glm::vec3 distanceToBeCovered;
	glm::vec3 movementStep;
	if (paused == false) {
		//get it to follow
		if (!selectedPath.empty())
		{

			current = getPosition();
			next = selectedPath.back();

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
				selectedPath.pop_back();
			}
		}
	}
	//cout << "choomah position = " << getPosition().x << " , " << getPosition().y << " , " << getPosition().z << " ) " << endl;

}

