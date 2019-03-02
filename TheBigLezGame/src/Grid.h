#pragma once
#include "Node.h"
#include "GameObject.h"
#include "Player.h"

#include <algorithm>
using namespace std;

class Grid: public GameObject{

public:

	Grid(glm::vec2 gridsize, float noderadius, glm::vec3 pos);

	void buildGrid(std::vector<GameObject*> &gameObjects, Shader *shader);

	bool checkGridCollision(GameObject* object, Node current);

	void update() override;

	void updateGrid(std::vector<GameObject*> &gameObjects, Shader* shader);

	glm::vec3 getPosition();

	float getSize();

	Node* getNodeFromPoint(glm::vec3 point);

	float clamp(float n, float upper, float lower);

	std::vector<glm::vec3> AStarPath(glm::vec3 start, glm::vec3 finish, std::vector<GameObject*>& gameObjects, Shader* shader);

	std::vector<Node*> getNeighbour(Node* current);

	int getDistance(Node nodeA, Node nodeB);

	std::vector<glm::vec3> retracePath(Node* startNode, Node* endNode, std::vector<GameObject*>& gameObjects, Shader* shader);

	std::vector<Node*> getPath();

	void addEndPoints(std::vector<glm::vec3> endPoints);

private:

	std::vector<std::vector<Node*>> rowVector;
	float nodeDiameter;

	glm::vec2 gridSize;
	int gridX, gridY;
	
	glm::vec3 position;

	Player::Character cube;

	std::vector<Node*> path;

	std::vector<glm::vec3> doors;

};