#pragma once
#include "Node.h"
#include "GameObject.h"

class Grid: public GameObject{

public:
	Grid(glm::vec2 gridsize, float noderadius, glm::vec3 pos);

	void buildGrid();

	void update() override;

private:

	Node **thisGrid;
	float nodeDiameter;
	glm::vec2 gridSize;
	glm::vec3 position;
};