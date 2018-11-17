#include "GameObject.h"

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
		renderComponent->setView(view);
		renderComponent->Draw();
	}
}
