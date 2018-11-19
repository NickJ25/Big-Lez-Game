#pragma once
#include "GameObject.h"
#include "TextureLoader.h"

class Skybox : public GameObject {
private:
	glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	GLuint m_VBO_texture; // Skybox texture

	string object = "assets/cube.obj";
	GLuint createCubeTexture(const char* image1, const char* image2, const char* image3, const char* image4, const char* image5, const char* image6);
public:
	Skybox(const char* image1, const char* image2, const char* image3, const char* image4, const char* image5, const char* image6) : GameObject(m_position, object.c_str()) {
		m_VBO_texture = createCubeTexture(image1, image2, image3, image4, image5, image6);
	};
	void update() override;

};