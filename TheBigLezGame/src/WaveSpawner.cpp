#include "WaveSpawner.h"

WaveSpawner::WaveSpawner(Grid* g) : GameObject(glm::vec3(0.0f,0.0f,0.0f))
{
	//set the grid
	grid = g;

	// numbers correspond to number of each choomah type per round
	vector<int> wave1;
	wave1.push_back(2), wave1.push_back(2), wave1.push_back(0), wave1.push_back(0);
	waves.push_back(wave1); 

	//set some random spawn points, 3 on each side out of view of the main building
	//first spawns
	spawnPointsBottom.push_back(glm::vec2(120.0f, 215.0f));
	spawnPointsTop.push_back(glm::vec2(-60.0f, -215.0f));
	spawnPointsRight.push_back(glm::vec2(195.0f, -115.0f));
	//second spawns
	//spawnPointsBottom.push_back(glm::vec2(200.0f, 215.0f));
	//spawnPointsTop.push_back(glm::vec2(110.0f, -215.0f));
	//spawnPointsRight.push_back(glm::vec2(195.0f, -115.0f));
	//third spawns
	//spawnPointsBottom.push_back(glm::vec2(-60.0f, 215.0f));
	//spawnPointsTop.push_back(glm::vec2(200.0f, -215.0f));
	//spawnPointsRight.push_back(glm::vec2(195.0f, -115.0f));

	initNPCs();
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
	int randomNumber = (rand() % 2);
	if (types[randomNumber] != lastType)
		return types[randomNumber];
	else
		if (randomNumber == 0)
			return 1;
		if (randomNumber == 1)
			return 2;

			return 0;
}
void WaveSpawner::spawnWave(std::vector<GameObject*> &gameObjects, int wavenumber, Shader* shader, PathManager* pathManager)
{
	//set empty pointer to array of floats
	vector<int> currentwave;

	// depending on what wave it currently is, assign current wave accordingly
	if (wavenumber == 0) for (int i = 0; i < 4; i++) currentwave.push_back(waves.at(0).at(i));
	if (wavenumber == 1) for (int i = 0; i < 4; i++) currentwave.push_back(waves.at(1).at(i));;
	if (wavenumber == 2) for (int i = 0; i < 4; i++) currentwave.push_back(waves.at(2).at(i));;
	if (wavenumber == 3) for (int i = 0; i < 4; i++) currentwave.push_back(waves.at(3).at(i));;

	//generate normal choomahs
	for (int j = 0; j < currentwave.size(); j++) {
		for (int i = 0; i < currentwave[j]; i++) {
			GameObject* choomah;

			//generate the choomahs from the vector
			if (j == 0)      choomah = new Enemy(normalChoomah);
			else if (j == 1) choomah = new Enemy(chargerChoomah);
			else if (j == 2) choomah = new Enemy(brawlerChoomah);
			else if (j == 3) choomah = new Enemy(bossChoomah);
			else		     choomah = new Enemy(normalChoomah);

			//select a spawn direction to spawn from
			currentType = getType();
			lastType = currentType;

			//set their properties
			choomah->setShader(shader);
			choomah->Move(glm::vec3(getSpawnCoord(currentType).x, -12.5f, getSpawnCoord(currentType).y));
			choomah->setAnimation(0.0f, 8.3f); // animation start is the number of seconds in (24 ticks per second), anim end is what you need to divide the animation length by to get the desired animation end number
			choomah->addCollision(glm::vec3(choomah->getPosition().x, -12.5f, -choomah->getPosition().y), 1.0, 1.0);

			cout << "choomah spawn position = " << choomah->getPosition().x << " , " << choomah->getPosition().y << " , " << choomah->getPosition().z << " ) " << endl;

			//get their path from the spawn point to a door
		    Enemy *e = dynamic_cast<Enemy*>(choomah);
			if (e)
				e->setPathEnd(getEndCoord(currentType));
			for (std::vector<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
			{
				Player *tmp = dynamic_cast<Player*>((*it));
				if (tmp)
				{
					e->setTarget(tmp);
					break;
				}
			}
			pathManager->addToQueue(choomah);

			// add them to the gameplay vector reference
			gameObjects.push_back(choomah);

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

	bossChoomah.fileLocation = "assets/Characters/Bumble-Brutus/bumblebrutus.dae";
	bossChoomah.name = "boss";

}