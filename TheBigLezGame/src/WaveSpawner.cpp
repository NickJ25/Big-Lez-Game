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
	spawnPoints.push_back(glm::vec2(120.0f, 215.0f));
	//spawnPoints.push_back(glm::vec2(-60.0f, -165.0f));
	//spawnPoints.push_back(glm::vec2(60.0f, -165.0f));
	//spawnPoints.push_back(glm::vec2(120.0f, -165.0f));
	//spawnPoints.push_back(glm::vec2(-120.0f, 195.0f));
	//spawnPoints.push_back(glm::vec2(-60.0f, 195.0f));
	//spawnPoints.push_back(glm::vec2(60.0f, 195.0f));
	//spawnPoints.push_back(glm::vec2(120.0f, 195.0f));
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

glm::vec2 WaveSpawner::getSpawnCoord()
{
	srand(time(0));
	float randomNumber = (rand() % spawnPoints.size());
	return spawnPoints.at(randomNumber);
}

void WaveSpawner::setEndCoords(std::vector<glm::vec3> e)
{
		endPoints = e;
}

glm::vec3 WaveSpawner::getEndCoord()
{
	srand(time(0));

	float randomNumber = (rand() % endPoints.size());
	return endPoints.at(randomNumber);

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

			//set their properties
			choomah->setShader(shader);
			//choomah->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			choomah->Move(glm::vec3(getSpawnCoord().x, -12.5f, getSpawnCoord().y));
			choomah->setAnim(0);
			choomah->addCollision(glm::vec3(choomah->getPosition().x, -12.5f, -choomah->getPosition().y), 1.0, 1.0);

			cout << "choomah spawn position = " << choomah->getPosition().x << " , " << choomah->getPosition().y << " , " << choomah->getPosition().z << " ) " << endl;

			//get their path from the spawn point to a door
		    Enemy *e = dynamic_cast<Enemy*>(choomah);
			if (e)
				e->setPathEnd(getEndCoord(), true);
			pathManager->addToQueue(choomah);

			// add them to the gameplay vector reference
			gameObjects.push_back(choomah);

		}
	}

}

void WaveSpawner::initNPCs()
{

	normalChoomah.fileLocation = "assets/Characters/Choomah-normal/choomahnormal.dae";
	normalChoomah.name = "normal";

	chargerChoomah.fileLocation = "assets/Characters/Choomah-charger/choomahcharger.dae";
	chargerChoomah.name = "charger";

	brawlerChoomah.fileLocation = "assets/Characters/Choomah-brawler/choomahbrawler.dae";
	brawlerChoomah.name = "brawler";

	bossChoomah.fileLocation = "assets/Characters/Bumble-Brutus/bumblebrutus.dae";
	bossChoomah.name = "boss";

}