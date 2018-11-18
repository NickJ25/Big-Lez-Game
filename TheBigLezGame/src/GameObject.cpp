#include "GameObject.h"

void GameObject::Move(glm::vec3 moveAmount)
{
	transformComponent->move(moveAmount);
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
