#include "PathManager.h"

PathManager::PathManager(Grid* g)
{
	grid = g;
	working = false;
}

void PathManager::addToQueue(GameObject* obj)
{
	pathQueue.push(obj);
}

void PathManager::update(std::vector<GameObject*>& gameObjects, Shader* shader)
{
	if (pathQueue.empty() == false) {
		GameObject *obj = pathQueue.front();
		Enemy* e = dynamic_cast<Enemy*>(obj);

		if (obj) {
			e->setPath(findPath(pathQueue.front(), e->getPathEnd(), gameObjects, shader), true);
			working = true;
		}

	}
}

std::vector<glm::vec3> PathManager::findPath(GameObject* obj, glm::vec3 end, std::vector<GameObject*> gameObjects, Shader* shader)
{

		pathQueue.pop();
		return grid->AStarPath(obj->getPosition(), end, gameObjects, shader);
}

std::queue<GameObject*> PathManager::getQueue()
{
	return pathQueue;
}