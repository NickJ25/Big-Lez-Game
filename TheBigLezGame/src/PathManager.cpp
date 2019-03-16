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
			if (e->getLocation() == false && e->getPath().empty()) 
			{
				e->setPath(findPath(pathQueue.front(), e->getOuterPathEnd().first, gameObjects, shader, 0 , false), true);
			}

			if (e->getLocation() == true && e->getCurrentTargetPosition() != e->getTarget()->getPosition() && e->getJump() == true)
			{
				e->setCurrentTargetPosition(e->getTarget()->getPosition());
				e->setPath(findPath(pathQueue.front(), e->getCurrentTargetPosition(), gameObjects, shader, 0, true), false);
			}

			pathQueue.pop();
			pathQueue.push(obj);

			cout << pathQueue.size() << endl;
			working = true;
		}

	}
}

std::vector<glm::vec3> PathManager::findPath(GameObject* obj, glm::vec3 end, std::vector<GameObject*> gameObjects, Shader* shader, int grid, bool ignoreCollsion)
{
	return grids.at(grid)->AStarPath(obj->getPosition(), end, gameObjects, shader, ignoreCollsion);
}
std::queue<GameObject*> PathManager::getQueue()
{
	return pathQueue;
}