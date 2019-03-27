#include "CollisionComponent.h"


glm::vec3 CollisionComponent::getPos()
{
	return centre;
}
glm::vec3 CollisionComponent::getScale()
{
	return scale;
}
float CollisionComponent::getHW()
{
	return halfWidth;
}

float CollisionComponent::getHH()
{
	return halfHeight;
}

float CollisionComponent::getTH()
{
	return halfTrueHeight;
}

void CollisionComponent::setCollider(glm::vec3 newPos)
{
	centre = newPos;
}

void CollisionComponent::moveCollider(glm::vec3 moveAmount)
{
	centre += moveAmount;
}

//
//bool CollisionComponent::checkCollisions(GameObject * a, GameObject * b)
//{
//	if (abs(a->getPosition().x - b->getPosition().x) > (a->getCollision().x + b->getCollision().x)) return false;
//	if (abs(a->getPosition().y - b->getPosition().y) > (a->getCollision().y + b->getCollision().y)) return false;
//	if (abs(a->getPosition().z - b->getPosition().z) > (a->getCollision().z + b->getCollision().z)) return false;
//	return true;
//}

//void CollisionComponent::checkCollisions(GameObject * a, GameObject * b, bool & x, bool & y, bool & z)
//{
//	if (abs(a->getPosition().x - b->getPosition().x) > (a->getCollision().x + b->getCollision().x)) {
//		x = false;
//	}
//	else {
//		x = true;
//	}
//	if (abs(a->getPosition().y - b->getPosition().y) > (a->getCollision().y + b->getCollision().y)) {
//		y = false;
//	}
//	else {
//		y = true;
//	}
//	if (abs(a->getPosition().z - b->getPosition().z) > (a->getCollision().z + b->getCollision().z)) {
//		z = false;
//	}
//	else {
//		z = true;
//	}
//}
