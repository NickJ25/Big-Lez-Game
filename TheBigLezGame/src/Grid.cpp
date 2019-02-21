#include "Grid.h"

Grid::Grid(glm::vec2 gridsize, float noderadius, glm::vec3 pos): GameObject(pos)
{

	nodeDiameter = noderadius * 2;
	gridSize = gridsize;
	position = pos;

	buildGrid();
}

void Grid::buildGrid()
{							
	glm::vec3 upVector = glm::vec3(0, 1, 0);
	glm::vec3 forwardVector = glm::vec3(0, 0, 1);
	glm::vec3 rightVector = glm::cross(upVector, forwardVector);


	glm::vec3 bottomLeft = position - rightVector * (gridSize.x / 2) - forwardVector * (gridSize.y / 2);
	thisGrid = new Node*[gridSize.y]; 

	for (int i = 0; i < gridSize.y; ++i) {
		for (int j = 0; j < gridSize.x; ++j) {

			glm::vec3 nodePos = bottomLeft + rightVector * (j* nodeDiameter + (nodeDiameter / 2)) + forwardVector * (i * nodeDiameter + (nodeDiameter / 2));
			thisGrid[i] = new Node[gridSize.x];
			thisGrid[i]->position = nodePos;
			std::cout << thisGrid[i]->position.x << " , " << thisGrid[i]->position.y << endl;
		}
	}
}

void Grid::update()
{

}