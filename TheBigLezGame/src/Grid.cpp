#include "Grid.h"

Grid::Grid(glm::vec2 gridsize, float noderadius, glm::vec3 pos): GameObject(pos)
{

	nodeDiameter = noderadius * 2;
	gridSize = gridsize;
	position = pos;

	gridX = int(gridSize.x / nodeDiameter);
	gridY = int(gridsize.y / nodeDiameter);

	cube.fileLocation = "assets/Props/Map/gridblock.dae";
	cube.name = "anything";
}

void Grid::buildGrid(std::vector<GameObject*> &gameObjects, Shader *shader)
{							
	glm::vec3 upVector = glm::vec3(0, 1, 0);
	glm::vec3 forwardVector = glm::vec3(0, 0, 1);
	glm::vec3 rightVector = glm::cross(upVector, forwardVector);


	glm::vec3 bottomLeft = position - rightVector * (gridSize.x / 2) - forwardVector * (gridSize.y / 2);
	thisGrid = new Node*[gridX]; 

	for (int i = 0; i < gridX; i++) {
		for (int j = 0; j < gridY; j++) {
			glm::vec3 nodePos = bottomLeft + rightVector * (i* nodeDiameter + (nodeDiameter / 2)) + forwardVector * (j * nodeDiameter + (nodeDiameter / 2));
			thisGrid[i] = new Node[gridY];
			thisGrid[i]->position = nodePos;
			std::cout << thisGrid[i]->position.x << " , " << thisGrid[i]->position.z << endl;

			GameObject* gridsquare;
			gridsquare = new Player(cube, glm::vec3(thisGrid[i]->position.x, -12.5f, thisGrid[i]->position.z));
			gridsquare->setShader(shader);
			gridsquare->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			gridsquare->Scale(glm::vec3(0.6f, 0.6f, 0.6f));
			gridsquare->setAnim(0);

			//cycle through game objects, check for obstructions, and assign accordingly
			std::vector<GameObject*>::iterator it;
			for (it = gameObjects.begin(); it != gameObjects.end(); it++)
			{
				GameObject* me = *it;
				if (me->getCollider)
				{
					if (checkGridCollision(me, thisGrid[i]) == true)
					{
						gridsquare->Move(glm::vec3(0.0f, 20.0f, 0.0f)); // to check the bastard is working
						thisGrid[i]->isBlocked == true;
					}
					else {
						thisGrid[i] == false;
					}
				}
			}

			gameObjects.push_back(gridsquare);
		}
	}
}

bool Grid::checkGridCollision(GameObject* a, Node* b)
{
		// Basic 2D collsion detection
		if (abs(a->getPosition().x - b->position.x) > (a->getCollider().getHW() + (nodeDiameter/2))) return false;
		if (abs(a->getPosition().z - b->position.z) > (a->getCollider().getHH() + (nodeDiameter / 2))) return false;
		return true;

}
void Grid::update()
{

}


glm::vec3 Grid::getPosition()
{
	return position;
}

float Grid::getSize()
{
	return nodeDiameter / 2;
}