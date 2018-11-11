#include "GameObject.h"

void GameObject::componentUpdate()
{

}

void GameObject::componentDraw()
{
	if (renderComponent != nullptr) {
		renderComponent->Draw();
	}
}
