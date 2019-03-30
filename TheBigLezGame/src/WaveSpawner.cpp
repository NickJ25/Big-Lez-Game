#include "WaveSpawner.h"
#include "Boss.h"

WaveSpawner::WaveSpawner() : GameObject(glm::vec3(0.0f,0.0f,0.0f))
{

	//set some random spawn points, 3 on each side out of view of the main building
	//first spawns
	spawnPointsBottom.push_back(glm::vec2(120.0f, 215.0f));
	spawnPointsTop.push_back(glm::vec2(-60.0f, -215.0f));
	spawnPointsRight.push_back(glm::vec2(195.0f, -115.0f));
	//second spawns
	spawnPointsBottom.push_back(glm::vec2(200.0f, 215.0f));
	spawnPointsTop.push_back(glm::vec2(110.0f, -215.0f));
	spawnPointsRight.push_back(glm::vec2(215.0f, -37.0f));
	//third spawns
	spawnPointsBottom.push_back(glm::vec2(-60.0f, 215.0f));
	spawnPointsTop.push_back(glm::vec2(200.0f, -215.0f));
	spawnPointsRight.push_back(glm::vec2(215.0f, 95.0f));

	initNPCs();

	//initialise the templates 
	choomah = new Enemy(normalChoomah);
	charger = new Enemy(chargerChoomah);
	brawler = new Enemy(brawlerChoomah);

	currentChoomah = choomah;

}

glm::vec2 WaveSpawner::getSpawnCoord(int type)
{
	srand(time(0));
	float randomNumber = 0;

	if (type == 0 && spawnPointsBottom.size() > 0) {
		randomNumber = (rand() % spawnPointsBottom.size());
		return spawnPointsBottom.at(randomNumber);
	}
	if (type == 1 && spawnPointsTop.size() > 0) {
		randomNumber = (rand() % spawnPointsTop.size());
		return spawnPointsTop.at(randomNumber);
	}
	/*if (type == "Left" && spawnPointsLeft.size() > 0) {
		randomNumber = (rand() % spawnPointsLeft.size());
		return spawnPointsLeft.at(randomNumber);
	}*/
	if (type == 2 && spawnPointsRight.size() > 0) {
		randomNumber = (rand() % spawnPointsRight.size());
		return spawnPointsRight.at(randomNumber);
	}
	cout << "incorrect string entered" << endl;
	return glm::vec2(0, 0);
}

void WaveSpawner::setEndCoords(std::vector<std::pair<glm::vec3, glm::vec3>> e, int type)
{
	if (type == 0)
		endPointsBottom = e;
	if (type == 1)
		endPointsTop = e;
	if (type == 2)
		endPointsRight = e;
	//if (type == "Left")
	//	endPointsLeft = e;
}

std::pair<glm::vec3 , glm::vec3> WaveSpawner::getEndCoord(int type)
{
	srand(time(0));
	float randomNumber;

	if (type == 0 && endPointsBottom.size() > 0) {
		float randomNumber = (rand() % endPointsBottom.size());
		return endPointsBottom.at(randomNumber);
	}
	if (type == 1 && endPointsTop.size() > 0) {
	    float randomNumber = (rand() % endPointsTop.size());
		return endPointsTop.at(randomNumber);
	}
	if (type == 2 && endPointsRight.size() > 0) {
		float randomNumber = (rand() % endPointsRight.size());
		return endPointsRight.at(randomNumber);
	}
	//if (type == "Left" && endPointsLeft.size() > 0) {
	//	float randomNumber = (rand() % endPointsLeft.size());
	//	return endPointsLeft.at(randomNumber);
	//}

}

int WaveSpawner::getType()
{
	srand(time(0));
	int randomNumber = rand() % 2;
	if (types[randomNumber] != lastType)
		return types[randomNumber];
	else
		if (randomNumber == 0)
			return 1;
		if (randomNumber == 1)
			return 2;
		if (randomNumber == 2)
			return 0;
}
void WaveSpawner::spawnWave(std::vector<GameObject*> &gameObjects, int wavenumber, Shader* shader, PathManager* pathManager, bool destinationVector, vector<GameObject*> &destination)
{
	
	//set empty pointer to vector of floats
	vector<int> currentwave;

	//enemy templates
	//GameObject* choomah = new Enemy(normalChoomah);
	//GameObject* charger = new Enemy(chargerChoomah);
	//GameObject* brawler = new Enemy(brawlerChoomah);

	//choomah = new Enemy(normalChoomah);
	//charger = new Enemy(chargerChoomah);
	//brawler = new Enemy(brawlerChoomah);

	//currentChoomah = choomah;

	// depending on what wave it currently is, assign current wave accordingly
	for (int i = 0; i < 4; i++) currentwave.push_back(waves.at(wavenumber).at(i));
	for (int i = 0; i < 4; i++) currentwave.push_back(waves.at(wavenumber).at(i));
	for (int i = 0; i < 4; i++) currentwave.push_back(waves.at(wavenumber).at(i));
	for (int i = 0; i < 4; i++) currentwave.push_back(waves.at(wavenumber).at(i));

		//generate normal choomahs
		for (int j = 0; j < currentwave.size(); j++) {
			for (int i = 0; i < currentwave[j]; i++) {

				//generate the choomahs from the vector
				if (j == 0) { choomah = new Enemy(normalChoomah); currentChoomah = choomah;
				}     //currentChoomah = choomah;
				else if (j == 1) { charger = new Enemy(chargerChoomah); currentChoomah = charger;
				}//currentChoomah = charger;
				else if (j == 2) { brawler = new Enemy(brawlerChoomah); currentChoomah = brawler;
				}// currentChoomah = brawler;
				else if (j == 3) {
					// has to be setup here to prevent include loops that would come by declaring its character in the header file
					Boss::Character bossChar;
					bossChar.fileLocation = "assets/Characters/Bumble-Brutus/bumblebrutus.dae";
					bossChar.name = "boss";
					choomah = new Boss(bossChar);
				}
				else {
					currentChoomah = new Enemy(normalChoomah);
				}

				//if not a boss choomah
				if (j != 3) {
					//select a spawn direction to spawn from
					currentType = getType();
					lastType = currentType;

					//set their properties
					if (currentChoomah) {

						glm::vec2 currentSpawn = getSpawnCoord(currentType);
						//setup enemy first
						Enemy *e = dynamic_cast<Enemy*>(currentChoomah);
						if (e) {
							e->reset(pathManager);
							e->setSpawnPoint(glm::vec3(currentSpawn.x, -12.5f, currentSpawn.y));
							e->setPathEnd(getEndCoord(currentType));
							e->setAnimValues(0.0f, 8.3f);
						}

						//then setup its gameobject parent
						currentChoomah->setShader(shader);
						currentChoomah->setMatrix(glm::mat4(1.0f));
						currentChoomah->Move(glm::vec3(currentSpawn.x, -12.5f, currentSpawn.y));
						currentChoomah->addCollision(glm::vec3(choomah->getPosition().x, -12.5f, -choomah->getPosition().z), 1.0, 1.0);


						for (std::vector<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
						{
							bool playerPassed = false;

							Player *tmp = dynamic_cast<Player*>((*it));
							if (tmp)
							{
								//	if (playerPassed = true)
								//	{
								e->setTarget(tmp);
								break;
								//	}
								/*	srand(time(0));
									int randomNumber = rand() % 4;
									if (randomNumber > 2) {
										e->setTarget(tmp);
										break;
									}
									else
									{
										playerPassed = true;
									}*/
							}
						}
						pathManager->addToQueue(currentChoomah);
					}
					if (j == 3)
					{
						//create the boss specially
						Boss* b = dynamic_cast<Boss*>(choomah);
						if (b) {
							b->setShader(shader);
							b->Move(b->getSpawnPoint());
							b->initialiseWaveSpawner(gameObjects, shader, pathManager);
							b->setAnimation(0.0f, 8.3f); // animation start is the number of seconds in (24 ticks per second), anim end is what you need to divide the animation length by to get the desired animation end number
							b->addCollision(glm::vec3(b->getPosition().x, -12.5f, -b->getPosition().y), 1.0, 1.0);
						}
					}
					//if this wavespawner is sending these enemies to a different vector
					if (destinationVector) {
						destination.push_back(currentChoomah);
						return;
					}
					else {
						// add them to the gameplay vector reference
						toBeSpawned.push_back(currentChoomah);
						return;
					}
				}
			}
		}
}

void WaveSpawner::initNPCs()
{

	normalChoomah.fileLocation = "assets/Characters/Choomah-normal/choomahbasic1.dae";
	normalChoomah.name = "normal";

	chargerChoomah.fileLocation = "assets/Characters/Choomah-charger/choomahcharger.dae";
	chargerChoomah.name = "charger";

	brawlerChoomah.fileLocation = "assets/Characters/Choomah-brawler/choomahbrawler.dae";
	brawlerChoomah.name = "brawler";

}