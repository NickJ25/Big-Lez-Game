#pragma once
#include <glm/vec3.hpp>

struct Node {

	Node();

	glm::vec3 position;

	void setBlocked(bool b)
	{
		isBlocked = b;
	}
	bool getBlocked()
	{
		return isBlocked;
	}
	float fCost, gCost = 0, hCost = 0;

	float gridX, gridY;


	float getFCost()
	{
		fCost = gCost + hCost;
		return fCost;
	}

	void SetParent(Node *p)
	{
			parent = p;
	}

	Node* getParent()
	{
		return parent;
	}

private:
	bool isBlocked = false;
	Node* parent;

};