#include "GameObject.h"

void GameObject::Move(glm::vec3 moveAmount)
{
	transformComponent->move(moveAmount);

	if (collisionComponent)
	{
		collisionComponent->move(moveAmount);
	}
}

void GameObject::Rotate(GLfloat degrees, glm::vec3 rotateAmount)
{
	transformComponent->rotate(degrees, rotateAmount);
}

void GameObject::Scale(glm::vec3 scaleAmount)
{
	transformComponent->scale(scaleAmount);
}

void GameObject::setShader(Shader * shader)
{
	objShader = shader;
	if (renderComponent != nullptr) {
		renderComponent->changeShader(shader);
	}
}

void GameObject::setAnim(int n) 
{
	renderComponent->setAnim(n);
}

glm::vec3 GameObject::getPosition()
{
	return transformComponent->getPosition();
}

void GameObject::addCollision(glm::vec3 pos, float hw, float hh, glm::vec3 scale)
{
	collisionComponent = new CollisionComponent(pos, scale, hw, hh);
}

CollisionComponent* GameObject::getCollider()
{
	return collisionComponent;
}

void GameObject::componentUpdate()
{

}

void GameObject::componentDraw(glm::mat4 view)
{
	if (renderComponent != nullptr) {
		renderComponent->setDrawMatrix(transformComponent->getMatrix());
		renderComponent->setView(view);
		renderComponent->Draw();
	}
}
