#include "Skybox.h"

GLuint Skybox::createCubeTexture(const char * image1, const char * image2, const char * image3, const char * image4, const char * image5, const char * image6)
{
	const char *cubeTexFiles[6] = { image1, image2, image3, image4, image5, image6 };

	// init buffer and sides
	GLuint texID;
	glGenTextures(1, &texID); // generate texture ID
	GLenum sides[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
					GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
					GL_TEXTURE_CUBE_MAP_POSITIVE_X,
					GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
					GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
					GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
	};

	// texture settings
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// read files using soil and set as skybox
	for (int i = 0; i < 6; i++) {
		int width, height;
		unsigned char *image = SOIL_load_image(cubeTexFiles[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(sides[i], 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	}

	return texID;
}

Skybox::Skybox(const char * image1, const char * image2, const char * image3, const char * image4, const char * image5, const char * image6)
{
	// Make Skybox Shader
	m_skyBoxShader = new Shader("src/skyboxShader.vert", "src/skyboxShader.geom", "src/skyboxShader.frag");

	float offset_side_cube = 1.0f;

	GLfloat skybox_vertices[] = {
		// Positions          
		-offset_side_cube,  offset_side_cube, -offset_side_cube, // front
		-offset_side_cube, -offset_side_cube, -offset_side_cube,
		offset_side_cube, -offset_side_cube, -offset_side_cube,
		offset_side_cube, -offset_side_cube, -offset_side_cube,
		offset_side_cube,  offset_side_cube, -offset_side_cube,
		-offset_side_cube,  offset_side_cube, -offset_side_cube,

		-offset_side_cube, -offset_side_cube,  offset_side_cube, // left
		-offset_side_cube, -offset_side_cube, -offset_side_cube,
		-offset_side_cube,  offset_side_cube, -offset_side_cube,
		-offset_side_cube,  offset_side_cube, -offset_side_cube,
		-offset_side_cube,  offset_side_cube,  offset_side_cube,
		-offset_side_cube, -offset_side_cube,  offset_side_cube,

		offset_side_cube, -offset_side_cube, -offset_side_cube, // right
		offset_side_cube, -offset_side_cube,  offset_side_cube,
		offset_side_cube,  offset_side_cube,  offset_side_cube,
		offset_side_cube,  offset_side_cube,  offset_side_cube,
		offset_side_cube,  offset_side_cube, -offset_side_cube,
		offset_side_cube, -offset_side_cube, -offset_side_cube,

		-offset_side_cube, -offset_side_cube,  offset_side_cube, // back
		-offset_side_cube,  offset_side_cube,  offset_side_cube,
		offset_side_cube,  offset_side_cube,  offset_side_cube,
		offset_side_cube,  offset_side_cube,  offset_side_cube,
		offset_side_cube, -offset_side_cube,  offset_side_cube,
		-offset_side_cube, -offset_side_cube,  offset_side_cube,

		-offset_side_cube,  offset_side_cube, -offset_side_cube, // top
		offset_side_cube,  offset_side_cube, -offset_side_cube,
		offset_side_cube,  offset_side_cube,  offset_side_cube,
		offset_side_cube,  offset_side_cube,  offset_side_cube,
		-offset_side_cube,  offset_side_cube,  offset_side_cube,
		-offset_side_cube,  offset_side_cube,  -offset_side_cube,

		-offset_side_cube, -offset_side_cube, -offset_side_cube, // bottom
		offset_side_cube, -offset_side_cube, -offset_side_cube,
		offset_side_cube, -offset_side_cube,  offset_side_cube,
		offset_side_cube, -offset_side_cube,  offset_side_cube,
		-offset_side_cube, -offset_side_cube,  offset_side_cube,
		-offset_side_cube, -offset_side_cube, -offset_side_cube
	};

	// VBO
	glGenBuffers(1, &m_VBO_vertices_textures);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_vertices_textures);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_vertices), &skybox_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// VAO
	glGenVertexArrays(1, &m_VAO_skybox);
	glBindVertexArray(m_VAO_skybox);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_vertices_textures);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Create Sample Cube
	m_VBO_texture = createCubeTexture(image1, image2, image3, image4, image5, image6);

	// Uniform buffer for splitscreen modelview data
	glGenBuffers(1, &m_uniform_buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, m_uniform_buffer);
	glBufferData(GL_UNIFORM_BUFFER, 4 * sizeof(glm::mat4), NULL, GL_DYNAMIC_DRAW);
}

void Skybox::draw(glm::mat4 viewMatrix)
{
	// draw skybox LAST in scene ( optimization in vertex shader )
	glDepthFunc(GL_LEQUAL); // optimization in shaders
	glUseProgram(m_skyBoxShader->getID());
	glBindVertexArray(m_VAO_skybox);
	glUniformMatrix4fv(glGetUniformLocation(m_skyBoxShader->getID(), "VP"), 1, GL_FALSE, glm::value_ptr(viewMatrix));

	//glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_uniform_buffer);
	//glm::mat4 * mv_matrix = (glm::mat4*)glMapBufferRange(GL_UNIFORM_BUFFER, 0, 2 * sizeof(glm::mat4), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	//for (int i = 0; i < 2; i++) {
	//	mv_matrix[i] = viewMatrix;
	//}
	//glUnmapBuffer(GL_UNIFORM_BUFFER);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_VBO_texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glUseProgram(0);
	glDepthFunc(GL_LESS); // return to default
}
