#include "CollisionComponent.h"

glm::vec3 CollisionComponent::getCollision()
{
	return m_collisionSize;
}

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
