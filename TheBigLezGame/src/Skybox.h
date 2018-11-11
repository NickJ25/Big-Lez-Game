#pragma once
#include "GameObject.h"

class Skybox : public GameObject {
private:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	string object = "assets/cube.obj";
	
public:
	Skybox(const char* folder, const char* image1, const char* image2, const char* image3, const char* image4, const char* image5, const char* image6) : GameObject(position, object.c_str) {
		const char *cubeTexFiles[6] = { image1, image2, image3, image4, image5, image6 };
	};
	void update() override;

};