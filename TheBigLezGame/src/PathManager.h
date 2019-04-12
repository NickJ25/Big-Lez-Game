#pragma once
#include "Grid.h"

//std library
#include <queue>

//forward declaration of enemy
class Enemy;
class PathManager {

public:
	//constructor
	PathManager();

	//add a gameobject to the path finding queue
	void addToQueue(GameObject* obj);

	//find a path
	std::vector<glm::vec3> findPath(GameObject* obj, glm::vec3 end, std::vector<GameObject*> gameObjects, Shader* shader, int grid, bool ignoreCollision);

	//return the queue
	std::queue<GameObject*> getQueue();

	//update the path manager
	void update(std::vector<GameObject*>& gameObjects, Shader* shader);

	//check if the path manager has calcualted a path yet this frame
	bool working;

	//add a grid for the pathmanager to find a path through
	void addGrid(Grid* g);

private:

	//hold multiple grids 
	std::vector<Grid*> grids;

	//path finding queue
	std::queue<GameObject*> pathQueue;

};