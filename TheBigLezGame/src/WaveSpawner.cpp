#include "WaveSpawner.h"

WaveSpawner::WaveSpawner(float r, glm::vec3 pos) : GameObject(pos)
{
	radius = r;
	position = pos;

	// numbers correspond to number of each choomah type per round
	vector<int> wave1;
	wave1.push_back(5), wave1.push_back(3), wave1.push_back(3), wave1.push_back(2);
	waves.push_back(wave1);

	initNPCs();
}

glm::vec2 WaveSpawner::getSpawnCoord()
{
	srand(time(0));
	float randomAngle = (rand() % 360);
	glm::vec2 spawnCoord = glm::vec2(cos(randomAngle)*radius, sin(randomAngle)*radius);

	return spawnCoord;
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
			if (j == 0)      choomah = new Player(normalChoomah, glm::vec3(getSpawnCoord().x, -12.5f, getSpawnCoord().y));
			else if (j == 1) choomah = new Player(chargerChoomah, glm::vec3(getSpawnCoord().x, -12.5f, getSpawnCoord().y));
			else if (j == 2) choomah = new Player(brawlerChoomah, glm::vec3(getSpawnCoord().x, -12.5f, getSpawnCoord().y));
			else if (j == 3) choomah = new Player(bossChoomah, glm::vec3(getSpawnCoord().x, -12.5f, getSpawnCoord().y));
			else		     choomah = new Player(normalChoomah, glm::vec3(getSpawnCoord().x, -12.5f, getSpawnCoord().y));

			//set their properties and add them to the gameplay vector reference
			choomah->setShader(shader);
			choomah->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			choomah->Scale(glm::vec3(0.6f, 0.6f, 0.6f));
			choomah->setAnim(0);
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