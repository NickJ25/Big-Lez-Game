#include "Boss.h"
#include "WaveSpawner.h"

Boss::Boss(Character character) : GameObject(character.fileLocation.c_str())
{

	// load in the boss' speech
	irrklang::ISoundSource* s1 = speechEngine->addSoundSourceFromFile("assets/Sounds/BumbleBrutus/BumbleBrutusLine1.wav");
	irrklang::ISoundSource* s2 = speechEngine->addSoundSourceFromFile("assets/Sounds/BumbleBrutus/BumbleBrutusLine2.wav");
	irrklang::ISoundSource* s3 = speechEngine->addSoundSourceFromFile("assets/Sounds/BumbleBrutus/BumbleBrutusLine3.wav");
	sounds.push_back(s1), sounds.push_back(s2), sounds.push_back(s3);

	//set to default walk animation
	setAnimation(0.0f, 4.4f);
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
	tmpPath.push_back(glm::vec3(50.0f, -12.5f, -100.0f));
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
	rightDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(100.0f, -12.5f, 40.0f), glm::vec3(80.0f, -12.5f, 40.0f)));


	privateSpawner->setEndCoords(bottomDoors, 0);
	privateSpawner->setEndCoords(topDoors, 1);
	privateSpawner->setEndCoords(rightDoors, 2);

	//set a random wave to current
	privateSpawner->setWave(normalWave);
	privateSpawner->setWave(chargerWave);
	privateSpawner->setWave(brawlerWave);


	//get all the waves ready to be spawned at any time
	while (brawlerObj.size() < 3) {
		privateSpawner->spawnWave(gameObjects, 0, shader, pathmanager, true, normalObj);
		privateSpawner->spawnWave(gameObjects, 1, shader, pathmanager, true, chargerObj);
		privateSpawner->spawnWave(gameObjects, 2, shader, pathmanager, true, brawlerObj);
	}

	//assign a current wave
	setWave();
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

	bool rotated = false; 

	if (dead == true)
	{
		if (deadSet == false)
		{
			//death sound and start animation
			setAnimation(9.167f, 1.479f);
			deadSet = true;
		}
		currentTime = glfwGetTime();
		float deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		deathAnimationTimer -= deltaTime;

		if (deathAnimationTimer <= 0) {
			//set to fully lying down frame
			setAnimation(10.0f, 1.479f);

			//then pause the model
			setStill(true);
			still = true;
		}

	}
	else {

		//if the boss is still moving
		if (stopped == false && soundSet == false)
		{
			privateEngine->play2D("assets/Sounds/BumbleBrutus/stomp.wav");// , irrklang::vec3df(getPosition().x, getPosition().y, getPosition().z), true);
			soundSet = true;
		}
		//if the boss isn't moving
		if (soundSet == true && stopped == true)
		{
			privateEngine->setAllSoundsPaused(true);

			//record the time and delta time
			currentTime = glfwGetTime();
			float deltaTime = currentTime - previousTime;
			previousTime = currentTime;

			//iterate down the speech timer until 0 then play a random line
			if (speechTimer > 0)
			{
				speechTimer -= deltaTime;
			}
			else
			{
				srand(time(0));
				float randomNumber = rand() % sounds.size();
				speechEngine->play2D(sounds.at(randomNumber));
				float clipSize = sounds.at(randomNumber)->getPlayLength() / 1000;
				speechTimer = 25.0f + clipSize;
			}
		}
		if (paused == false) {
			//get it to follow
			if (!selectedPath.empty())
			{
				current = getPosition();
				next = selectedPath.back();

				//get angle between the current and the next node
				distanceToBeCovered = next - current;

				rotation = glm::normalize(distanceToBeCovered); // rotation we want to be at

				//rotation is reset every frame with new matrix
				glm::vec3 currentRot = glm::vec3(1.0f, 0.0f, 0.0f); // current rotation

				//calculate angle between the two vectors
				float dotProd = glm::dot(currentRot, rotation);

				//clamp it to between -pi and pi
				if (dotProd > 3.1415f) {
					dotProd = fmod(dotProd, 3.1415f);
				}
				else
					if (dotProd < -3.1415f)
					{
						dotProd = fmod(dotProd, -3.1415f);
					}

				//find the angle from this value
				float angle = acos(dotProd);

				//calculate the cross of the two vectors
				glm::vec3 crossProd = glm::cross(currentRot, rotation);

				//if the result indicated it is upside down, rotate anti-clockwise instead of clockwise
				if (glm::dot(glm::normalize(crossProd), glm::vec3(0.0f, 1.0f, 0.0f)) < 0)
				{
					angle = -angle;
				}

				movementStep = glm::normalize(distanceToBeCovered) * velocity;


				//reset the rotation
				glm::mat4 tempMat(1.0f);

				//calculate the translation 
				tempMat = glm::translate(tempMat, getPosition());
				tempMat = glm::translate(tempMat, movementStep);

				//reapply the rotation
				tempMat = glm::rotate(tempMat, angle + glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

				//set the matrix
				setMatrix(tempMat);

				//move the bounding box with the model without applying rotation
				if (getCollider())
					getCollider()->setCollider(tempMat[3]);

				if (glm::vec3(std::round(getPosition().x), -12.5f, std::round(getPosition().z)) == next)
				{
					selectedPath.pop_back();
					rotated = false;
				}
			}
			else
			{
				stopped = true;
			}
		}
	}
}

int Boss::getCurrentWave()
{
	//return a random wave
	srand(time(0));
	int type = (rand() % bossWaves.size());
	return type;
}

void Boss::spawnMinions(std::vector<GameObject*> &g, Shader* shader, PathManager* pathmanager)
{
	if (animationTimer > 0)
	{
		if (animating == true) {

			if (still == true) {
				still = false;
				setStill(false);
			}

			//if normal choomahs do the stomp animation
			if (animType == "normal")
				setAnimation(12.5f, 1.11f);
			//if the chargers, do the waving hand animation
			if (animType == "charger")
				setAnimation(13.75f, 1.0f);
			//if the brawlers, do the beating chest animation
			if (animType == "brawler")
				setAnimation(10.83f, 1.225f);

			animationTimer--;
		}
	}
	else {
		//standing still
		if (stopped == true) {
			animating = false;
			animationTimer = 144;
			setStill(true);
			still = true;
		}
	}

	if (canSpawn == true && stopped == true)
	{
		//find the anim type by checking which enemy is spawned
		Enemy* temp = dynamic_cast<Enemy*>(currentObj.at(0));
		if (temp)
			animType = temp->getName();

		//if the wave is not set, then set it
		if (waveSet == false)
		{
			current = bossWaves.at(currentWave);
			std::vector<int> tmp = bossWaves.at(currentWave);
			int numOfChoomahs = 0;
			for (vector<int>::iterator it = tmp.begin(); it < tmp.end(); ++it)
			{
				numOfChoomahs += (*it);
			}
			numToBeSpawned = numOfChoomahs;
			animating = true;
			waveSet = true;

		}

		//spawn one enemy per frame for efficiency
		while (numToBeSpawned > 0) {
			privateSpawner->spawnEnemy(currentObj, g);
			numToBeSpawned--;
		}

		//reset whichever wave has just been dispensed
		if (currentWave == 0) {
			for (vector<GameObject*>::iterator it = normalObj.begin(); it < normalObj.end(); ++it)
			{
				Enemy *e = dynamic_cast<Enemy*>((*it));
				if (e)
					e->reset(pathmanager);
			}
		}
		if (currentWave == 1) {
			for (vector<GameObject*>::iterator it = chargerObj.begin(); it < chargerObj.end(); ++it)
			{
				Enemy *e = dynamic_cast<Enemy*>((*it));
				if (e)
					e->reset(pathmanager);
			}
		}
		if (currentWave == 2) {
			for (vector<GameObject*>::iterator it = brawlerObj.begin(); it < brawlerObj.end(); ++it)
			{
				Enemy *e = dynamic_cast<Enemy*>((*it));
				if (e)
					e->reset(pathmanager);
			}
		}
			waveSpawned = true;
			canSpawn = false;
			currentWave = NULL;

			//set a new wave
			setWave();
	}
}

void Boss::setWave()
{
	//choose a random wave, then set all the relevant information to that waves variables
	srand(time(0));
	int randomNumber = rand() % 3;
	if (randomNumber == 0) {
		currentObj = normalObj;
		current = normalWave;
		currentWave = 0;
	}
	if (randomNumber == 1) {
		currentObj = chargerObj;
		current = chargerWave;
		currentWave = 1;
	}
	if (randomNumber == 2) {
		currentObj = brawlerObj;
		current = brawlerWave;
		currentWave = 2;
	}
}

void Boss::checkFieldEmpty(std::vector<GameObject*> g)
{
	//iterate through gameobjects and increment the counter if an enemy is found
	int counter = 0;
	std::vector<GameObject*>::iterator it;
	for (it = g.begin(); it != g.end(); it++)
	{
		Enemy *e = dynamic_cast<Enemy*>((*it));
		if (e && e->getDeath() == false)
			counter++;
	}
	//if there are no enemies in the scene
	if (counter <= 0)
	{
		canSpawn = true;
		if (waveSpawned == true)
		{
			waveSpawned == false;
			waveSet = false;
		}
	}
	else
	{
		if (waveSpawned == true) {
			canSpawn = false;
		}
	}
}

void Boss::setPathEnd(glm::vec3 p)
{
	outerPathEnd.push_back(p);
}

void Boss::setHealth(float num)
{
	health += num;
}

glm::vec3 Boss::getSpawnPoint()
{
	return selectedSpawnPoint;
}

float Boss::getHealth()
{
	//return health as a percentage of the screen width for the health bar
	return (health / 2400.0f) * 1280.0f;
}

void Boss::takeDamage(float damage)
{
	//take damage while taking into consideration the armour value
	health -= damage/100 * armour;

	//if the boss has no more health
	if (health <= 0) {
		health = 0;
		death();
	}
}

void Boss::death()
{
	//set death animation and timer the length of it -1 frame
	if (dead == false) {
		dead = true;
		setAnimation(8.75f, 1.48f);
		setPauseFrame(10.0f);
	}
}