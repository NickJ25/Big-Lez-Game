#pragma once
#include "Node.h"
#include "GameObject.h"
#include "Player.h"

class Grid: public GameObject{

public:

	Grid(glm::vec2 gridsize, float noderadius, glm::vec3 pos);

	void buildGrid(std::vector<GameObject*> &gameObjects, Shader *shader);

	bool checkGridCollision(GameObject* object, Node* current);

	void update() override;

	glm::vec3 getPosition();

	float getSize();

private:

	Node **thisGrid;
	float nodeDiameter;
	glm::vec2 gridSize;
	int gridX, gridY;
	glm::vec3 position;

	Player::Character cube;

};