#include "WaveSpawner.h"

WaveSpawner::WaveSpawner(Grid* g) : GameObject(glm::vec3(0.0f,0.0f,0.0f))
{
	//set the grid
	grid = g;

	// numbers correspond to number of each choomah type per round
	vector<int> wave1;
	wave1.push_back(1), wave1.push_back(0), wave1.push_back(0), wave1.push_back(0);
	waves.push_back(wave1); 

	//set some random spawn points, 4 on each side out of view of the main building
	spawnPointsBottom.push_back(glm::vec2(120.0f, 215.0f));
	spawnPointsTop.push_back(glm::vec2(120.0f, 215.0f));
	spawnPointsRight.push_back(glm::vec2(210.0f, 105.0f));
	spawnPointsLeft.push_back(glm::vec2(-130.0f, 95.0f));
	//spawnPointsBottom.push_back(glm::vec2(120.0f, 215.0f));
	//spawnPointsTop.push_back(glm::vec2(120.0f, 215.0f));
	//spawnPointsLeft.push_back(glm::vec2(120.0f, 215.0f));
	//spawnPointsRight.push_back(glm::vec2(120.0f, 215.0f));
	//spawnPoints.push_back(glm::vec2(-130.0f, -155.0f));
	//spawnPoints.push_back(glm::vec2(-70.0f, -160.0f));
	//spawnPoints.push_back(glm::vec2(70.0f, -155.0f));
	//spawnPoints.push_back(glm::vec2(130.0f, -160.0f));
	//spawnPoints.push_back(glm::vec2(-130.0f, 185.0f));
	//spawnPoints.push_back(glm::vec2(-70.0f, 190.0f));
	//spawnPoints.push_back(glm::vec2(70.0f, 185.0f));
	//spawnPoints.push_back(glm::vec2(130.0f, 190.0f));

	initNPCs();
}

glm::vec2 WaveSpawner::getSpawnCoord(string type)
{
	srand(time(0));
	float randomNumber = 0;

	if (type == "Bottom" && spawnPointsBottom.size() > 0) {
		randomNumber = (rand() % spawnPointsBottom.size());
		return spawnPointsBottom.at(randomNumber);
	}
	if (type == "Top" && spawnPointsTop.size() > 0) {
		randomNumber = (rand() % spawnPointsTop.size());
		return spawnPointsTop.at(randomNumber);
	}
	if (type == "Left" && spawnPointsLeft.size() > 0) {
		randomNumber = (rand() % spawnPointsLeft.size());
		return spawnPointsLeft.at(randomNumber);
	}
	if (type == "Right" && spawnPointsRight.size() > 0) {
		randomNumber = (rand() % spawnPointsRight.size());
		return spawnPointsLeft.at(randomNumber);
	}
	cout << "incorrect string entered" << endl;
	return glm::vec2(0, 0);
}

void WaveSpawner::setEndCoords(std::vector<glm::vec3> e, string type)
{
	if (type == "Bottom")
		endPointsBottom = e;
	if (type == "Top")
		endPointsTop = e;
	if (type == "Left")
		endPointsLeft = e;
	if (type == "Right")
		endPointsRight = e;
}

glm::vec3 WaveSpawner::getEndCoord(string type)
{
	srand(time(0));
	float randomNumber;

	if (type == "Bottom" && endPointsBottom.size() > 0) {
		float randomNumber = (rand() % endPointsBottom.size());
		return endPointsBottom.at(randomNumber);
	}
	if (type == "Top" && endPointsTop.size() > 0) {
		float randomNumber = (rand() % endPointsTop.size());
		return endPointsTop.at(randomNumber);
	}
	if (type == "Left" && endPointsLeft.size() > 0) {
		float randomNumber = (rand() % endPointsLeft.size());
		return endPointsLeft.at(randomNumber);
	}
	if (type == "Right" && endPointsRight.size() > 0) {
		float randomNumber = (rand() % endPointsRight.size());
		return endPointsRight.at(randomNumber);
	}

}

string WaveSpawner::getType()
{
	//srand(time(0));
	//int randomNumber = (rand() % types->size());
	//return types[randomNumber];
	return "Right";
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
			//set their properties
			choomah->setShader(shader);
			choomah->Move(glm::vec3(getSpawnCoord(currentType).x, -12.5f, getSpawnCoord(currentType).y));
			choomah->setAnimation(0.0f, 8.3f); // animation start is the number of seconds in (24 ticks per second), anim end is what you need to divide the animation length by to get the desired animation end number
			choomah->addCollision(glm::vec3(choomah->getPosition().x, -12.5f, -choomah->getPosition().y), 1.0, 1.0);

			cout << "choomah spawn position = " << choomah->getPosition().x << " , " << choomah->getPosition().y << " , " << choomah->getPosition().z << " ) " << endl;

			//get their path from the spawn point to a door
		    Enemy *e = dynamic_cast<Enemy*>(choomah);
			if (e)
				e->setPathEnd(getEndCoord(currentType), true);
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

	normalChoomah.fileLocation = "assets/Characters/Choomah-normal/choomahbasic.dae";
	normalChoomah.name = "normal";

	chargerChoomah.fileLocation = "assets/Characters/Choomah-charger/choomahcharger.dae";
	chargerChoomah.name = "charger";

	brawlerChoomah.fileLocation = "assets/Characters/Choomah-brawler/choomahbrawler.dae";
	brawlerChoomah.name = "brawler";

	bossChoomah.fileLocation = "assets/Characters/Bumble-Brutus/bumblebrutus.dae";
	bossChoomah.name = "boss";

}