#include "WaveSpawner.h"

WaveSpawner::WaveSpawner() : GameObject(glm::vec3(0.0f,0.0f,0.0f))
{

	// numbers correspond to number of each choomah type per round
	vector<int> wave1;
	wave1.push_back(5), wave1.push_back(3), wave1.push_back(3), wave1.push_back(2);
	waves.push_back(wave1); 

	//set some random spawn points, 4 on each side out of view of the main building
	spawnPoints.push_back(glm::vec2(-120.0f, -165.0f));
	spawnPoints.push_back(glm::vec2(-60.0f, -165.0f));
	spawnPoints.push_back(glm::vec2(60.0f, -165.0f));
	spawnPoints.push_back(glm::vec2(120.0f, -165.0f));
	spawnPoints.push_back(glm::vec2(-120.0f, 195.0f));
	spawnPoints.push_back(glm::vec2(-60.0f, 195.0f));
	spawnPoints.push_back(glm::vec2(60.0f, 195.0f));
	spawnPoints.push_back(glm::vec2(120.0f, 195.0f));

	initNPCs();
}

glm::vec2 WaveSpawner::getSpawnCoord()
{
	srand(time(0));
	float randomNumber = (rand() % 8);
	return spawnPoints.at(randomNumber);
}

void WaveSpawner::spawnWave(std::vector<GameObject*> &gameObjects, int wavenumber, Shader* shader)
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
			if (j == 0)      choomah = new Player(normalChoomah);
			else if (j == 1) choomah = new Player(chargerChoomah);
			else if (j == 2) choomah = new Player(brawlerChoomah);
			else if (j == 3) choomah = new Player(bossChoomah);
			else		     choomah = new Player(normalChoomah);

			//set their properties and add them to the gameplay vector reference
			choomah->setShader(shader);
			choomah->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			choomah->Move(glm::vec3(getSpawnCoord().x, getSpawnCoord().y, 0.0f));
			choomah->setAnim(0);
			choomah->addCollision(glm::vec3(choomah->getPosition().x, 0.0f, -choomah->getPosition().y), 1.0, 1.0);
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