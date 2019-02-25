#include "Node.h"

Node::Node(float size)
{
	gCost = size;
	hCost = size;

	fCost = size * 2;
}