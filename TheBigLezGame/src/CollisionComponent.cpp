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

void CollisionComponent::setScale(glm::vec3 newScale)
{
	halfWidth *= newScale.x;
	halfHeight *= newScale.z;
}

void CollisionComponent::moveCollider(glm::vec3 moveAmount)
{
	centre += moveAmount;
}