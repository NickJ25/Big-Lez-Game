#include "Image.h"

Image::Image(const char* filename) {
	imageShader = new Shader("src/Image.vert", "src/Image.frag");
	image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);
	// Generate and load image data
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	// Generate geometry
	imageShader->use();

	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_VBO2);
	glGenBuffers(1, &m_EBO);
	
	// Make second buffer for texture coords
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(backgroundCoords), backgroundCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid*)0);
	m_rotation = glm::rotate(m_rotation, (float)glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	m_rotation = glm::scale(m_rotation, glm::vec3(1.0f, 50.0f, 1.0f));
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	SOIL_free_image_data(image);

	m_proj = glm::ortho(0.0f, 1280.0f / 720.0f, 0.0f, 100.0f);
	m_view = glm::lookAt(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


}
void Image::rotate(GLfloat radians) {
	m_rotation = glm::rotate(m_rotation, (float)glm::radians(radians), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Image::draw()
{
	imageShader->use();
	glUniformMatrix4fv(glGetUniformLocation(imageShader->getID(), "imgRotation"), 1, GL_FALSE, glm::value_ptr(m_rotation));
	glUniformMatrix4fv(glGetUniformLocation(imageShader->getID(), "imgProj"), 1, GL_FALSE, glm::value_ptr(m_proj));
	glUniformMatrix4fv(glGetUniformLocation(imageShader->getID(), "imgView"), 1, GL_FALSE, glm::value_ptr(m_view));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
