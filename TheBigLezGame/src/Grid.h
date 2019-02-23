#pragma once
#include "Node.h"
#include "GameObject.h"
#include "Player.h"

using namespace std;

class Grid: public GameObject{

public:

	Grid(glm::vec2 gridsize, float noderadius, glm::vec3 pos);

	void buildGrid(std::vector<GameObject*> &gameObjects, Shader *shader);

	bool checkGridCollision(GameObject* object, Node* current);
	bool checkaltGridCollision(GameObject* object, Node current);

	void update() override;

	void updateGrid(std::vector<GameObject*> &gameObjects, Shader* shader);

	glm::vec3 getPosition();

	float getSize();

private:

	//Node **thisGrid;
	std::vector<std::vector<Node>> rowVector;
	float nodeDiameter;
	glm::vec2 gridSize;
	int gridX, gridY;
	glm::vec3 position;

	Player::Character cube;

};