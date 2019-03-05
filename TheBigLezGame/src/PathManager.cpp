#include "PathManager.h"

PathManager::PathManager()
{
	working = false;
}

void PathManager::addToQueue(GameObject* obj)
{
	pathQueue.push(obj);
}

void PathManager::addGrid(Grid* g) 
{
	grids.push_back(g);

}

void PathManager::update(std::vector<GameObject*>& gameObjects, Shader* shader)
{
	if (pathQueue.empty() == false) {
		GameObject *obj = pathQueue.front();
		Enemy* e = dynamic_cast<Enemy*>(obj);

		if (obj) {
			if (e->getLocation() == false) {
				e->setPath(findPath(pathQueue.front(), e->getPathEnd(), gameObjects, shader, 0 ), true);
			}
			else {
				e->setPath(findPath(pathQueue.front(), e->getPathEnd(), gameObjects, shader, 1), false);
			}
			working = true;
		}

	}
}

std::vector<glm::vec3> PathManager::findPath(GameObject* obj, glm::vec3 end, std::vector<GameObject*> gameObjects, Shader* shader, int grid)
{

	pathQueue.pop();
	Enemy *e;
	e = dynamic_cast<Enemy*>(obj);
	if (e)
	{
		std::vector<Grid*>::iterator it;
		for (it = grids.begin(); it != grids.end(); it++)
		{
				return grids.at(grid)->AStarPath(obj->getPosition(), end, gameObjects, shader);
		}
	}
}
std::queue<GameObject*> PathManager::getQueue()
{
	return pathQueue;
}