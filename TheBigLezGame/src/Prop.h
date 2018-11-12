#pragma once
#include "GameObject.h"
#include "Shader.h"

class Prop : public GameObject 
{
private:

public:
	Prop(const char* filename, glm::vec3 position) : GameObject(position, filename) {
		
	}
	void setShadertemp(Shader* shader) {
		renderComponent->changeShader(shader);
	}
	void update() override;
};