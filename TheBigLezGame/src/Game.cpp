#include "Game.h"
#include <Windows.h>
#include "Gun.h"

vector<GameObject*> gameObjects;
vector<GameObject*> collisionObjs;
Skybox* skybox;
Shader *toonShader;
WaveSpawner* waveSpawner;
Grid* pathFindingGrid;
PathManager* pathManager;
Prop* collisionTest;

GameObject* sassy;

// Initalize Two Camera
//Camera lezCamera(glm::vec3(110.0f, 12.5f, 190.0f), FREECAM);

rt3d::materialStruct material0 = {
	{0.0f, 0.8f, 0.2f, 1.0f}, // ambient
	{0.5f, 1.0f, 0.5f, 1.0f}, // diffuse
	{0.0f, 0.1f, 0.0f, 1.0f}, // specular
	2.0f  // shininess
};

int diffuse = 0;
int specular = 1;
float shininess = 32.0f;


void Game::init()
{
	std::cout << "Game.cpp Init" << std::endl;
	toonShader = new Shader("src/toonShader.vert", "src/toonShader.frag");

	skybox = new Skybox("assets/Skybox/back.bmp", "assets/Skybox/front.bmp",
						"assets/Skybox/right.bmp", "assets/Skybox/left.bmp",
						"assets/Skybox/top.bmp", "assets/Skybox/bottom.bmp");

	showBoundingBoxes = false;

	////	Init Objects	////
	GameObject* dirLight = new DirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.9f, 0.9f, 0.9f));
	dirLight->setShader(toonShader);
	gameObjects.push_back(dirLight);

	

	GameObject* environment = new Prop("assets/Props/Map/envMap.dae", glm::vec3(0.0f, 100.0f, 0.0f));

	//GameObject* spotLight = new SpotLight(mainCamera->getCameraPos(), mainCamera->getCameraFront(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.1f), 0.4, 3);
	//spotLight->setShader(toonShader);
	//gameObjects.push_back(spotLight);
	//GameObject* pointLight = new PointLight(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.09f, 0.05f, 0.09f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.09f, 0.32f));
	//pointLight->setShader(toonShader);
	//gameObjects.push_back(pointLight);
	
	//GameObject* table = new Prop("assets/Props/Table/table.obj", glm::vec3(0.0f, 0.0f, 0.0f));
	//table->setShader(toonShader);
	//gameObjects.push_back(table);
	//GameObject* couch = new Prop("assets/Props/Couch/couch.obj", glm::vec3(5.0f, 0.0f, 5.0f));
	//couch->setShader(toonShader);
	//gameObjects.push_back(couch);

	environment->setShader(toonShader);
	environment->Move(glm::vec3(0.0f, 100.0f, 0.0f));
	gameObjects.push_back(environment);

	// Characters
	Player::Character BigLez;
	BigLez.fileLocation = "assets/Characters/BigLez/lez.dae";
	BigLez.name = "Leslie";
	BigLez.health = 100;
	BigLez.walkSpeed = 10;

	Player::Character Sassy;
	Sassy.fileLocation = "assets/Characters/Sassy/sassy.dae";
	Sassy.name = "Sassy";

	Player::Character cube;
	cube.fileLocation = "assets/Props/Map/gridblock.dae";
	cube.name = "boundingbox";

	//Player::Character doorCollider;
	//cube.fileLocation = "assets/Props/Map/gridblock.dae";
	//cube.name = "doorbox";

	//GameObject* bigLez = new Player(doorCollider);
	//bigLez->setShader(toonShader);
	//bigLez->setAnim(0);
	//bigLez->Move(glm::vec3(45.0f, -12.5f, -26.0f));
	//bigLez->addCollision(glm::vec3(45.0f, -12.5f, -26.0f), 1.0f, 1.0f);
	//gameObjects.push_back(bigLez);


	sassy = new Player(ControllerComponent::CONTROLLER1, Sassy, glm::vec3(45.0f, -12.5f, 20.0f)); // Change to prop is issue?
	sassy->setShader(toonShader);
	sassy->Move(glm::vec3(45.0f, -12.5f, 20.0f));
	sassy->setAnimation(5.0f, 1.0f);
	sassy->addCollision(glm::vec3(45.0f, -12.5f, 20.0f), 5.0f, 5.0f);
	gameObjects.push_back(sassy);

	mainPlayer = new Player(ControllerComponent::KEYBOARD, BigLez, glm::vec3(0.0f, 0.0f, 0.0f));
	mainPlayer->setShader(toonShader);
	mainPlayer->Move(glm::vec3(45.0f, -12.5f, 20.0f));
	//mainPlayer->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//mainPlayer->Scale(glm::vec3(0.6f, 0.6f, 0.6f));
	//mainPlayer->setAnim(0);
	mainPlayer->setAnimation(5.0f, 1.0f);
	gameObjects.push_back(mainPlayer);

	GameObject* lezShotgun = new Gun("assets/Weapons/Shotgun/lezshotgun.dae", "Shotgun", 8, 8, false);
	lezShotgun->setShader(toonShader);
	lezShotgun->setAnimation(0.0f, 1.0f);
	mainPlayer->addWeapon(dynamic_cast<Weapon*> (lezShotgun));
	gameObjects.push_back(lezShotgun);

	GameObject* lezTest = new Prop("assets/Props/Table/Table.dae", glm::vec3(0.0f, 0.0f, 0.0f));
	lezTest->Move(glm::vec3(-10.0f, 0.0f, -10.0f));
	cout << "lez test pos:" << lezTest->getPosition().x << " " << lezTest->getPosition().y << " " << lezTest->getPosition().z << "----------------------" << endl;
	lezTest->setShader(toonShader);
	lezTest->Rotate(-90.0f, glm::vec3(1.0, 0.0, 0.0));
	lezTest->addCollision(glm::vec3(-10.0f, 0.0f, -10.0f), 50, 50);
	gameObjects.push_back(lezTest);


	// add environmental collision boxes for pathfinding an' such
	glm::vec3 fenceScaleVertical = glm::vec3(4.0f, 4.0f, 35.0f);
	glm::vec3 fenceScaleHorizontal = glm::vec3(35.0f, 4.0f, 4.0f);
	glm::vec3 test = glm::vec3(2.5, 2.5, 2.5);
	GameObject* Fence;

//#pragma region Fences

	for (int i = 0; i < 20; i++)
	{
		Fence = new Obstacle("collider", glm::vec3(0.0,0.0,0.0));


		glm::vec3 scaleFactor = fenceScaleVertical;
		if (i >= 4 && i < 14) scaleFactor = fenceScaleHorizontal;
		if (i == 14) scaleFactor = glm::vec3(2.0f, 4.0, 25.0f);
		if (i == 15 || i == 16) scaleFactor = glm::vec3(18.0f, 4.0, 2.0);
		if (i == 17 || i == 18) scaleFactor = glm::vec3(8.0f, 4.0, 2.0);
		if (i == 19) scaleFactor = glm::vec3(2.0f, 4.0, 4.0);

			//apply the selected scale first
			Fence->Scale(scaleFactor);
			
			glm::vec3 pos;

			//fences
			if (i == 0) { pos = glm::vec3(-13.0f*scaleFactor.x, 0.0f*scaleFactor.y, 0.9f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); Fence->Move(glm::vec3(-13.0f, 0.0f, 0.9f)); }
			if (i == 1) { pos = glm::vec3(-13.0f*scaleFactor.x, 0.0f*scaleFactor.y, -2.6f*scaleFactor.z); 	Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); Fence->Move(glm::vec3(-13.0f, 0.0f, -2.6f));}
			if (i == 2) { pos = glm::vec3(37.0f*scaleFactor.x, 0.0f*scaleFactor.y, 0.9f*scaleFactor.z); 	Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); Fence->Move(glm::vec3(37.0f, 0.0f, 0.9f));}
			if (i == 3) { pos = glm::vec3(37.0f*scaleFactor.x, 0.0f*scaleFactor.y, -2.6f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); Fence->Move(glm::vec3(37.0f, 0.0f, -2.6f));  }
			if (i == 4) { pos = glm::vec3(-4.2f*scaleFactor.x, 0.0f*scaleFactor.y, -41.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); Fence->Move(glm::vec3(-4.2f, 0.0f, -41.0f));   }
			if (i == 5) { pos = glm::vec3(-0.2f*scaleFactor.x, 0.0f*scaleFactor.y, -41.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); Fence->Move(glm::vec3(-0.2f, 0.0f, -41.0f)); }
			if (i == 6) { pos = glm::vec3(3.2f*scaleFactor.x, 0.0f*scaleFactor.y, -41.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); Fence->Move(glm::vec3(3.2f, 0.0f, -41.0f));}
			if (i == 7) { pos = glm::vec3(6.7f*scaleFactor.x, 0.0f*scaleFactor.y, -41.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); Fence->Move(glm::vec3(6.7f, 0.0f, -41.0f));}

			//house on the right
			if (i == 8) { scaleFactor = fenceScaleVertical;  pos = glm::vec3(50.0f*scaleFactor.x, 0.0f*scaleFactor.y, 0.8f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z+10.0); Fence->Move(glm::vec3(50.0f, 0.0f, 0.8f));}
			if (i == 9) { scaleFactor = fenceScaleVertical;  pos = glm::vec3(55.0f*scaleFactor.x, 0.0f*scaleFactor.y, 0.8f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z+10.0); Fence->Move(glm::vec3(55.0f, 0.0f, 0.8f));}
			if (i == 10){ scaleFactor = fenceScaleVertical;  pos = glm::vec3(60.0f*scaleFactor.x, 0.0f*scaleFactor.y, 0.8f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z+10.0); Fence->Move(glm::vec3(60.0f, 0.0f, 0.8f));}

			//house on the left
			if (i == 11) { pos = glm::vec3(-5.0f*scaleFactor.x, 0.0f*scaleFactor.y, 0.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); Fence->Move(glm::vec3(-5.0f, 0.0f, 0.0f));}
			if (i == 12) { pos = glm::vec3(-5.0f*scaleFactor.x, 0.0f*scaleFactor.y, 5.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); Fence->Move(glm::vec3(-5.0f, 0.0f, 5.0f));}
			if (i == 13) { pos = glm::vec3(-5.0f*scaleFactor.x, 0.0f*scaleFactor.y, 10.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); Fence->Move(glm::vec3(-5.0f, 0.0f, 10.0f));
			}

			//house in the middle 
			if (i == 14){ pos = glm::vec3(2.0f*scaleFactor.x, 0.0f*scaleFactor.y, 0.5f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); Fence->Move(glm::vec3(2.0f, 0.0f, 0.5f));}
			if (i == 15){ pos = glm::vec3(1.0f*scaleFactor.x, 0.0f*scaleFactor.y, -7.5f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); Fence->Move(glm::vec3(1.0f, 0.0f, -7.5f));}
			if (i == 16){ pos = glm::vec3(1.0f*scaleFactor.x, 0.0f*scaleFactor.y, 17.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); Fence->Move(glm::vec3(1.0f, 0.0f, 17.0f));}
			if (i == 17){ pos = glm::vec3(8.0f*scaleFactor.x, 0.0f*scaleFactor.y, -7.5f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); Fence->Move(glm::vec3(8.0f, 0.0f, -7.5f));}
			if (i == 18){ pos = glm::vec3(8.0f*scaleFactor.x, 0.0f*scaleFactor.y, 17.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); Fence->Move(glm::vec3(8.0f, 0.0f, 17.0f));}
			if (i == 19){ pos = glm::vec3(47.0f*scaleFactor.x, 0.0f*scaleFactor.y, 3.0f*scaleFactor.z); Fence->addCollision(pos, scaleFactor.x, scaleFactor.z); Fence->Move(glm::vec3(47.0f, 0.0f, 3.0f));}

			//add collision objects to the game objects vector
			gameObjects.push_back(Fence);

	}

//#pragma endregion

	//first initialise a Fector containing door information
	std::vector<std::pair<glm::vec3, glm::vec3>> bottomDoors, topDoors, leftDoors, rightDoors;

	bottomDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(83.0f, -12.5f, 46.0f), glm::vec3(83.0f, -12.5f, 38.0f)));
	//bottomDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(43.0f, -12.5f, 50.0f), glm::vec3(43.0f, -12.5f, 30.0f)));

	//topDoors.push_back(std::pair<glm::vec3, glm::vec3> (glm::vec3(83.0f, -12.5f, -30.0f), glm::vec3(83.0f,-12.5f,-10.0f)));
	topDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(43.0f, -12.5f, -30.0f), glm::vec3(43.0f, -12.5f, -10.0f)));

	rightDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(100.0f, -12.5f, -6.0f), glm::vec3(80.0f, -12.5f, -6.0f)));
	rightDoors.push_back(std::pair<glm::vec3, glm::vec3>(glm::vec3(100.0f, -12.5f, 32.0f), glm::vec3(80.0f, -12.5f, 32.0f)));


	//grid has to be the last game object added
	pathFindingGrid = new Grid(glm::vec2(1250, 1250), 2.0f, glm::vec3(0.0f, 0.0f, 0.0f), "boundingbox");
	pathFindingGrid->buildGrid(gameObjects, toonShader);

	//initialise the path manager
	pathManager = new PathManager();
	pathManager->addGrid(pathFindingGrid);

	//set up the wavespawner
	waveSpawner = new WaveSpawner();

	// numbers correspond to number of each choomah type per round
	vector<int> wave1;
	wave1.push_back(0), wave1.push_back(0), wave1.push_back(0), wave1.push_back(1);

	//add this wave to the wave spawner
	waveSpawner->setWave(wave1);

	waveSpawner->setEndCoords(bottomDoors, 0);
	waveSpawner->setEndCoords(topDoors, 1);
	waveSpawner->setEndCoords(rightDoors, 2);
	//dlc
	//waveSpawner->setEndCoords(leftDoors, "Left");

	//prepare wave 1 to be spawned
	waveSpawner->spawnWave(gameObjects, 0, toonShader, pathManager, false);


	resumeBtn = new Button(Button::NORMAL, glm::vec2(640.0, 460.0), "Resume");
	mainMenuBtn = new Button(Button::NORMAL, glm::vec2(640.0, 340.0), "Quit");
	pauseBackground = new Image("assets/Art/tempBackground.png", glm::vec2(640.0, 360.0));

	testtxt = new Text(glm::vec2(590.0, 445.0), "assets/Fonts/Another_.ttf");
	testtxt2 = new Text(glm::vec2(600.0, 325.0), "assets/Fonts/Another_.ttf");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool Game::checkCollision(GameObject* a, GameObject* b)
{
	if (abs(a->getCollider()->getPos().x - b->getCollider()->getPos().x) > (a->getCollider()->getHW() + b->getCollider()->getHW())) return false;
	if (abs(a->getCollider()->getPos().z - b->getCollider()->getPos().z) > (a->getCollider()->getHH() + b->getCollider()->getHW())) return false;

	//penetrationDepthX = a->getCollider()->getHW() + b->getCollider()->getHW() - a->getCollider()->getPos().x - b->getCollider()->getPos().x;
	//penetrationDepthZ = a->getCollider()->getHH() + b->getCollider()->getHW() - a->getCollider()->getPos().z - b->getCollider()->getPos().z;

	return true;
}

bool Game::pointIsAbovePlane(const glm::vec3 & P, const glm::vec3 & n, float d)
{
	return glm::dot(n, P) + d > FLT_EPSILON;
}

char Game::computePointMask(glm::vec3 p, Enemy* e)
{
	glm::vec3 center = p;
	glm::vec2 radii = glm::vec2(e->getCollider()->getHW(), e->getCollider()->getHH());

	char mask = 0;
	if (pointIsAbovePlane(p, nright, -center.x - radii.x))
	{
		mask |= 1;// +x
	}
	if (pointIsAbovePlane(p, nleft, center.x - radii.x))
	{
		mask |= 2;	// -x
	}
	if (pointIsAbovePlane(p, nup, -center.z - radii.y))
	{
		mask |= 4;	// +y
	}
	if (pointIsAbovePlane(p, ndown, center.z - radii.y))
	{
		mask |= 8;	// -y
	}
	return mask;
}

glm::vec3 Game::getFaceNormal(glm::vec3 p, Enemy* e)
{
	char mask = computePointMask(p, e);
	glm::vec3 normal = glm::vec3(0, 0, 0);
	if ((mask & 1) == 1)	// +x
	{
		normal += nright;
	}
	if ((mask & 2) == 2)	// -x
	{
		normal += nleft;
	}
	if ((mask & 4) == 4)	// +y
	{
		normal += nup;
	}
	if ((mask & 8) == 8)	// -y
	{
		normal += ndown;
	}
	return normalize(normal);
}

void removeEnemies(std::vector<GameObject*> & gameObjects)
{
	std::vector<GameObject*>::iterator it = gameObjects.begin();
	while(it != gameObjects.end())
	{

		Enemy* e = dynamic_cast<Enemy*>((*it));
		if (e)
		{
			it = gameObjects.erase(it);
		}
		else {
			++it;
		}
	}
}

void Game::update()
{
	if(isGameRunning == true)
	{
		//check if an enemy is due to be spawned, and if so create it
		std::vector<GameObject*> empty;
		waveSpawner->spawnEnemy(empty, gameObjects);

		for (int i = 0; i < gameObjects.size(); i++) {
			if (gameObjects[i] != nullptr) {
				gameObjects[i]->componentUpdate();
				gameObjects[i]->update();

				//update enemy AI 
				Enemy *e = dynamic_cast<Enemy*>(gameObjects[i]);
				if (e)
				{
					e->update();
				}

				Boss *b = dynamic_cast<Boss*>(gameObjects[i]);
				if (b)
				{
					b->update();
					b->checkFieldEmpty(gameObjects);
					b->spawnMinions(gameObjects, toonShader, pathManager);
					cout << endl;
				}
			}
		}

		//collision checking loop
		for (vector<GameObject*>::iterator it = gameObjects.begin(); it < gameObjects.end() - 1; ++it)
		{
			for (vector<GameObject*>::iterator it1 = it + 1; it1 < gameObjects.end(); ++it1) // we make sure that we check a collision between the same objcts only once
			{
				if ((*it)->getCollider() && (*it1)->getCollider()) {

					Enemy *t1 = dynamic_cast<Enemy*>((*it));
					Enemy *t2 = dynamic_cast<Enemy*>((*it1));
					Player *p1 = dynamic_cast<Player*>((*it));
					Player *p2 = dynamic_cast<Player*>((*it1));
					if (t1 || t2 && p1 || p2)
					{
						//cout << endl;
					}
					if (checkCollision((*it), (*it1)) == true)
					{
						//an enemy is colliding with something
						//if it is another enemy
						Enemy *e1 = dynamic_cast<Enemy*>((*it));
						Enemy *e2 = dynamic_cast<Enemy*>((*it1));

						//if they are both enemies
						if (e1 && e2) {
							//do contact resolution here 

							// dlc - get contact normal
							//contactNormal = getFaceNormal(e1->getPosition(), e2);

							//calculate distance between points
							float dist = glm::distance(e1->getPosition(), e2->getPosition());
							float penetration = dist - (e1->getCollider()->getHW() + e2->getCollider()->getHW());

							//if there is a positive penetration
							if (penetration <= 0) {

								//shuffle both away from eachother - this will help for spawning but they will still pile up on the player, but you'll be dead 
								//before you notice
								//e1->Move(glm::vec3(-5.0f, 0.0f, 0.0f));
								//e2->Move(glm::vec3(0.0f, 0.0f, 1.0f));
							}
						}
						else
						{
							
							Player *p1 = dynamic_cast<Player*>((*it));
							Player *p2 = dynamic_cast<Player*>((*it1));
							//if there is a player, enemy collision

							if (e1 || e2)
							{
								//cout << endl;
							}

							if (p1 || p2)
							{
								//cout << endl;
							}
							if (e1 && p2 || e2 && p1)
							{
								//check which one is the enemy, then set to attack animation
								if (e1)
								{
									e1->setMoving(false);
									if(!e1->getInjured())
									e1->setAnimValues(3.6f, 1.36);
								}
								if (e2)
								{
									e2->setMoving(false);
									if (!e2->getInjured())
									e2->setAnimValues(3.6f, 1.36);
								}
							}
						}
						
					}
				}

			}
		}
		// Everything else
		if(mainPlayer->hasPlayerAttacked()) cout << "FIRE ZE MISSILES!" << endl;
	}
	
	if (Input::keyboard1.keys[GLFW_KEY_P])
	{
		isGameRunning = false;	
		g_window = glfwGetCurrentContext();
		glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	if (Input::keyboard1.keys[GLFW_KEY_B])
	{
		if (clicked == false) {
			removeEnemies(gameObjects);
			clicked = true;
		}
	}

	if (Input::keyboard1.keys[GLFW_KEY_N])
	{
		if (clicked == true) {
			clicked = false;
		}
	}

	if (isGameRunning == false) 
	{
		vector<GameObject*>::iterator it;
		for (it = gameObjects.begin(); it != gameObjects.end(); it++)
		{
			(*it)->setPaused(true);
		}
		if (resumeBtn->buttonClick()) 
		{
			vector<GameObject*>::iterator it;
			for (it = gameObjects.begin(); it != gameObjects.end(); it++)
			{
				(*it)->setPaused(false);
			}
			isGameRunning = true;
			glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		if (mainMenuBtn->buttonClick()) 
		{
			glfwDestroyWindow(g_window);
			exit(0);
		}

	}
	glm::vec3 ray_Test(0.0f, 0.0f, 0.0f);
	ray_Test = mainPlayer->getPosition() + mainPlayer->getCamera()->getCameraFront() * 1.0f;
	cout << "Ray: " << ray_Test.x << " " << ray_Test.y << " " << ray_Test.z << endl;

	if (Input::keyboard1.keys[GLFW_KEY_C]) {
		sassy->Move(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (Input::keyboard1.keys[GLFW_KEY_V]) {
		sassy->Move(glm::vec3(-1.0f, 0.0f, 0.0f));
	}

	if (Input::keyboard1.keys[GLFW_KEY_1]) {

		if (showBoundingBoxes == false) {
			vector<GameObject*>::iterator it;
			for (it = gameObjects.begin(); it != gameObjects.end(); it++)
			{
				Player *tmp = dynamic_cast<Player*>(*it);
				if (tmp != nullptr)
				{
					if (tmp->getCharacter().name == "boundingbox")
					{
						if (showBoundingBoxes == false)
							(*it)->setDraw(true);
					}
				}
			}
			showBoundingBoxes = true;
		}
	}

	if (Input::keyboard1.keys[GLFW_KEY_Q]) {

		vector<GameObject*>::iterator it;
		for (it = gameObjects.begin(); it != gameObjects.end(); it++)
		{
			(*it)->setPaused(true);

			Enemy *tmp = dynamic_cast<Enemy*>(*it);
			if (tmp != nullptr) {
				tmp->setPaused(true);
			}
		}
	}

	if (Input::keyboard1.keys[GLFW_KEY_E]) {

		vector<GameObject*>::iterator it;
		for (it = gameObjects.begin(); it != gameObjects.end(); it++)
		{
			(*it)->setPaused(false);

			Enemy *tmp = dynamic_cast<Enemy*>(*it);
			if (tmp != nullptr) {
				tmp->setPaused(false);
			}

		}
	}


	if (Input::keyboard1.keys[GLFW_KEY_2]) {

		if (showBoundingBoxes == true) {
			vector<GameObject*>::iterator it;
			for (it = gameObjects.begin(); it != gameObjects.end(); it++)
			{
				Player *tmp = dynamic_cast<Player*>(*it);
				if (tmp != nullptr)
				{
					if (tmp->getCharacter().name == "boundingbox")
					{
							(*it)->setDraw(false);
					}
				}
			}
			showBoundingBoxes = false;
		}
	}

	if (Input::keyboard1.keys[GLFW_KEY_X]) {
		mainPlayer->playAnimation();
	}

	if (Input::keyboard1.keys[GLFW_KEY_M]) {

		if (takeDamage == false) {
			vector<GameObject*>::iterator it;
			for (it = gameObjects.begin(); it != gameObjects.end(); it++)
			{
				Enemy *tmp = dynamic_cast<Enemy*>(*it);
				if (tmp)
				{
					tmp->takeDamage(0.05f);
				}
			}
			takeDamage = true;
		}
	}

	if (Input::keyboard1.keys[GLFW_KEY_O]) {

		if (takeDamage == true) {
			takeDamage = false;
		}
	}

	//update one path per frame so the computer doesnt melt
	if (pathManager->working == false) {
		pathManager->update(gameObjects, toonShader);
	}
	if (pathManager->working == true)
		pathManager->working = false;

	//cout << "cpos: " << lezCamera.getCameraPos().x << " " << lezCamera.getCameraPos().z << endl;
	const Uint8 *keys = SDL_GetKeyboardState(NULL); /// ----------------------------------------------------------------------REMOVE
	if (keys[SDL_SCANCODE_ESCAPE]) SDL_SetRelativeMouseMode(SDL_FALSE); // TEMP
	else SDL_SetRelativeMouseMode(SDL_TRUE);
}


void Game::draw()
{
	//glEnable(GL_DEPTH_TEST);
	glUseProgram(toonShader->getID());
	glUniform1i(glGetUniformLocation(toonShader->getID(), "material.diffuse1"), diffuse);
	glUniform1i(glGetUniformLocation(toonShader->getID(), "material.specular1"), specular);
	glUniform1f(glGetUniformLocation(toonShader->getID(), "material.shininess"), shininess);

	//glUniform3f(glGetUniformLocation(toonShader->getID(), "viewPos"), lezCamera.getCameraPos().x, lezCamera.getCameraPos().y, lezCamera.getCameraPos().z);
	glUniform3f(glGetUniformLocation(toonShader->getID(), "viewPos"), mainPlayer->getCamera()->getCameraPos().x, mainPlayer->getCamera()->getCameraPos().y, mainPlayer->getCamera()->getCameraPos().z);
	glm::mat4 projection = (glm::perspective(float(glm::radians(60.0f)), 1280.0f / 720.0f, 1.0f, 150.0f));

	skybox->draw(projection * glm::mat4(glm::mat3(mainPlayer->getCamera()->lookAtMat())));

	//skybox->draw(projection * glm::mat4(glm::mat3(lezCamera.lookAtMat())));

	if (isGameRunning == false)
	{
		// Draws pause menu
		resumeBtn->draw();
		mainMenuBtn->draw(); 
		testtxt->draw("Resume", glm::vec3(1.0f, 1.0f, 1.0f));
		testtxt2->draw("Quit", glm::vec3(1.0f, 1.0f, 1.0f));
		pauseBackground->draw();
	}

	for (int i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i] != nullptr) {
			gameObjects[i]->componentDraw(mainPlayer->getCamera()->lookAtMat());
			//gameObjects[i]->componentDraw(lezCamera.lookAtMat());
		}
	}
	
}
