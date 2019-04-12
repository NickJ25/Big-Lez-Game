#pragma once
//glm
#include <glm/vec3.hpp>

//structure that defines the nodes that make up a grid for path finding
struct Node {

	//constructor
	Node();

	//nodes position in space
	glm::vec3 position;

	//set and get if the node is blocked by an obstacle
	void setBlocked(bool b);
	bool getBlocked();

	//costs for calculating fastest route
	float fCost, gCost = 0, hCost = 0;

	//containers
	float gridX, gridY;

	//return F cost
	float getFCost();

	//return and set the nodes parents - nodes on the grid are essentially an undirected graph
	void SetParent(Node *p);
	Node* getParent();

private:
	bool isBlocked = false;
	Node* parent;

};