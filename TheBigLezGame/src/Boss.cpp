#include "Boss.h"
#include "WaveSpawner.h"

Boss::Boss(Character character) : GameObject(character.fileLocation.c_str())
{

	//intialise spawnable waves
	normalWave.push_back(3), normalWave.push_back(0), normalWave.push_back(0), normalWave.push_back(0);
	chargerWave.push_back(0), chargerWave.push_back(3), chargerWave.push_back(0), chargerWave.push_back(0);
	brawlerWave.push_back(0), brawlerWave.push_back(0), brawlerWave.push_back(3), brawlerWave.push_back(0);

	bossWaves.push_back(normalWave), bossWaves.push_back(chargerWave), bossWaves.push_back(brawlerWave);
	current = bossWaves.at(0);

	//initialise a wave spawner 
	privateSpawner = new WaveSpawner();

	paused = false;
	velocity = 0.1;
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
	spawnPoints.push_back(glm::vec3(215.0f, -12.5f, -240.0f));

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

void Boss::initialiseWaveSpawner(vector<GameObject*> gameObjects, Shader* shader, PathManager* pathmanager) {

	//first initialise a vector containing door information
	std::vector<std::pair<glm::vec3, glm::vec3>> bottomDoors, topDoors, leftDoors, rightDoors;

	topDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(83.0f, -12.5f, -30.0f), glm::vec3(83.0f, -12.5f, -10.0f)));
	topDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(43.0f, -12.5f, -30.0f), glm::vec3(43.0f, -12.5f, -10.0f)));

	bottomDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(83.0f, -12.5f, 50.0f), glm::vec3(83.0f, -12.5f, 30.0f)));
	bottomDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(43.0f, -12.5f, 50.0f), glm::vec3(43.0f, -12.5f, 30.0f)));

	rightDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(100.0f, -12.5f, -10.0f), glm::vec3(80.0f, -12.5f, -10.0f)));
	rightDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(100.0f, -12.5f, 30.0f), glm::vec3(80.0f, -12.5f, 30.0f)));


	privateSpawner->setEndCoords(bottomDoors, 0);
	privateSpawner->setEndCoords(topDoors, 1);
	privateSpawner->setEndCoords(rightDoors, 2);

	//assign a current wave
	setWave();

	//set a random wave to current
	privateSpawner->setWave(current);

	//get all the waves ready to be spawned at any time
	privateSpawner->spawnWave(gameObjects, 0, shader, pathmanager, normalObj);
	privateSpawner->spawnWave(gameObjects, 0, shader, pathmanager, chargerObj);
	privateSpawner->spawnWave(gameObjects, 0, shader, pathmanager, brawlerObj);

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
		else
		{
			stopped = true;
		}
	}
}

int Boss::getCurrentWave()
{
	srand(time(0));
	int type = (rand() % bossWaves.size());
	return type;
}

void Boss::spawnMinions(std::vector<GameObject*> &g, Shader* shader, PathManager* pathmanager)
{

	if (canSpawn == true && stopped == true)
	{
		if (waveSet == false)
		{
			currentWave = getCurrentWave();
			current = bossWaves.at(currentWave);
			std::vector<int> tmp = bossWaves.at(currentWave);
			int numOfChoomahs = 0;
			for (vector<int>::iterator it = tmp.begin(); it < tmp.end(); ++it)
			{
				numOfChoomahs += (*it);
			}
			numToBeSpawned = numOfChoomahs;
			waveSet = true;
		}

		privateSpawner->spawnEnemy(currentObj, g);

		numToBeSpawned--;
		if (numToBeSpawned == 0)
		{
			waveSpawned = true;
			canSpawn = false;
			currentWave = NULL;
			//set a new wave;
			setWave();
		}
	}
}

void Boss::checkFieldEmpty(std::vector<GameObject*> g)
{
	int counter = 0;
	std::vector<GameObject*>::iterator it;
	for (it = g.begin(); it != g.end(); it++)
	{
		Enemy *e = dynamic_cast<Enemy*>((*it));
		if (e)
			counter++;
	}
	if (counter <= 0)
	{
		canSpawn = true;
		if (waveSpawned == true)
		{
			waveSpawned == false;
		}
	}
	else
	{
		if(waveSpawned == true)
		canSpawn = false;
	}
}

void Boss::setPathEnd(glm::vec3 p)
{
	outerPathEnd.push_back(p);
}

glm::vec3 Boss::getOuterPathEnd(int position)
{
	return outerPathEnd.at(position);
}

glm::vec3 Boss::getSpawnPoint()
{
	return selectedSpawnPoint;
}