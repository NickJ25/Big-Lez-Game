#pragma once
#include "GameObject.h"
#include "TextureLoader.h"

class Skybox{
private:
	glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	GLuint m_VBO_texture; // Skybox texture
	GLuint m_VAO_skybox;
	GLuint m_VBO_vertices_textures;

	//splitscreen modelview buffer
	GLuint m_uniform_buffer;

	Shader *m_skyBoxShader;

	GLuint createCubeTexture(const char* image1, const char* image2, const char* image3, const char* image4, const char* image5, const char* image6);
public:
	Skybox(const char* image1, const char* image2, const char* image3, const char* image4, const char* image5, const char* image6);
	void draw(glm::mat4 viewMatrix);

};