#pragma once
#include "Grid.h"
#include "Enemy.h"
#include <queue>

#include "Enemy.h"

class PathManager {

public:
	PathManager();

	void addToQueue(GameObject* obj);

	std::vector<glm::vec3> findPath(GameObject* obj, glm::vec3 end, std::vector<GameObject*> gameObjects, Shader* shader, int grid);

	std::queue<GameObject*> getQueue();

	void update(std::vector<GameObject*>& gameObjects, Shader* shader);

	bool working;

	void addGrid(Grid* g);

private:

	std::vector<Grid*> grids;
	std::queue<GameObject*> pathQueue;

};