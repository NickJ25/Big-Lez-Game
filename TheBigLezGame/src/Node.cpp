#include "Node.h"

Node::Node()
{

}

void Node::setBlocked(bool b)
{
	isBlocked = b;
}
bool Node::getBlocked()
{
	return isBlocked;
}

float Node::getFCost()
{
	fCost = gCost + hCost;
	return fCost;
}

void Node::SetParent(Node *p)
{
	parent = p;
}

Node* Node::getParent()
{
	return parent;
}