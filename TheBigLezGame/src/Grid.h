#pragma once
#include "Node.h"
#include "GameObject.h"
#include "Player.h"
#include "Obstacle.h"

//std library
#include <algorithm>
using namespace std;

class Grid: public GameObject{

public:

	Grid(glm::vec2 gridsize, float noderadius, glm::vec3 pos, std::string b);

	//generate the grid
	void buildGrid(std::vector<GameObject*> &gameObjects, Shader *shader);

	//look for colliders inside the grid
	bool checkGridCollision(GameObject* object, Node current);

	//inherited from game object
	void update() override;

	//update grid collisions (for debugging)
	void updateGrid(std::vector<GameObject*> &gameObjects, Shader* shader);

	//return the position
	glm::vec3 getPosition();

	//return the grid size
	float getSize();

	//translate a point in space to a node in the grid
	Node* getNodeFromPoint(glm::vec3 point);
	
	//utility clamp function to keep co-ordinates within the bounds of the grid
	float clamp(float n, float upper, float lower);

	//a star implementation
	std::vector<glm::vec3> AStarPath(glm::vec3 start, glm::vec3 finish, std::vector<GameObject*>& gameObjects, Shader* shader, bool ignoreCollision);

	//return a nodes neighbours
	std::vector<Node*> getNeighbour(Node* current);

	//return the distance between two nodes
	int getDistance(Node nodeA, Node nodeB);

	//work out the path between two nodes
	std::vector<glm::vec3> retracePath(Node* startNode, Node* endNode, std::vector<GameObject*>& gameObjects, Shader* shader);

	//return the path
	std::vector<Node*> getPath();

private:

	//container variables
	std::vector<std::vector<Node*>> rowVector;
	float nodeDiameter;

	//size variables
	glm::vec2 gridSize;
	int gridX, gridY;
	
	//holds the position
	glm::vec3 position;
	
	//holds the currently calculated path
	std::vector<Node*> path;

	//for use in debugging
	Obstacle::Character cube;
	std::string boundingType;
};