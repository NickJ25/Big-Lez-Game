#include "Image.h"


void Image::init(unsigned char* image)
{
	imageShader = new Shader("src/Image.vert", "src/Image.frag");

	// Generate and load image data
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_imgWidth, m_imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

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
	if(isMenu) m_model = glm::scale(m_model, glm::vec3((float)Input::SCREEN_WIDTH / 2, (float)Input::SCREEN_HEIGHT / 2, 1.0f));
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	SOIL_free_image_data(image);

	m_proj = glm::ortho(0.0f, (float)Input::SCREEN_WIDTH, 0.0f, (float)Input::SCREEN_HEIGHT, 0.0f, 100.0f);
	m_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

Image::Image(const char * filename, glm::vec2 screenPos, bool ismenu)
{
	m_image = SOIL_load_image(filename, &m_imgWidth, &m_imgHeight, 0, SOIL_LOAD_RGBA);
	m_model = glm::translate(m_model, glm::vec3(screenPos.x, screenPos.y, 0.0f));

	posX = screenPos.x;
	posY = screenPos.y;
	isMenu = ismenu;
	if (m_image) {
		init(m_image);
	}
	else {
		std::cout << "IMAGE ERROR: Image: " << filename << "was not found!" << std::endl;
	}
}

Image::Image(const char * filename, glm::vec2 screenPos, int width, int height, bool ismenu)
{
	m_Width = width;
	m_Height = height;
	m_image = SOIL_load_image(filename, &m_imgWidth, &m_imgHeight, 0, SOIL_LOAD_RGBA);
	m_model = glm::translate(m_model, glm::vec3(screenPos, 0.0f));


	posX = screenPos.x;
	posY = screenPos.y;
	isMenu = ismenu;

	if (m_image) {
		init(m_image);
	}
	else {
		std::cout << "IMAGE ERROR: Image: " << filename << "was not found!" << std::endl;
	}
}

Image::~Image()
{
	delete imageShader;
	imageShader = nullptr;
}

void Image::changeImage(std::string newImage)
{
	m_image = SOIL_load_image(newImage.c_str(), &m_imgWidth, &m_imgHeight, 0, SOIL_LOAD_RGBA);
	init(m_image);
}

void Image::translate(glm::vec2 position)
{
	m_model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0));
}

void Image::rotate(GLfloat radians) {
	m_model = glm::rotate(m_model, (float)glm::radians(radians), glm::vec3(0.0f, 1.0f, 0.0f));
	currentRot += radians;
}

void Image::scale(glm::vec2 scale, bool resetMat) {
	if (!resetMat) {
		glm::mat4 temp(1.0f);
		temp = glm::translate(temp, glm::vec3(posX, posY, 0.0f));
		if (isMenu)
			temp = glm::scale(temp, glm::vec3(640.0f, 360.0f, 1.0f));

		temp = glm::rotate(temp, currentRot, glm::vec3(0.0f, 1.0f, 0.0f));
		temp = glm::scale(temp, glm::vec3(scale.x, scale.y, 0.0f));
		m_model = glm::scale(m_model, glm::vec3(scale, 0.0f));
		m_model = temp;// glm::scale(m_model, glm::vec3(scale, 0.0f));
	}
	else {
		m_model = glm::scale(m_model, glm::vec3(scale, 0.0f));
	}
}

void Image::draw()
{
	imageShader->use();
	glUniformMatrix4fv(glGetUniformLocation(imageShader->getID(), "imgRotation"), 1, GL_FALSE, glm::value_ptr(m_model));
	glUniformMatrix4fv(glGetUniformLocation(imageShader->getID(), "imgProj"), 1, GL_FALSE, glm::value_ptr(m_proj));
	glUniformMatrix4fv(glGetUniformLocation(imageShader->getID(), "imgView"), 1, GL_FALSE, glm::value_ptr(m_view));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
