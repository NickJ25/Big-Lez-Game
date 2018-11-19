#include "Skybox.h"

GLuint Skybox::createCubeTexture(const char * image1, const char * image2, const char * image3, const char * image4, const char * image5, const char * image6)
{
	const char *cubeTexFiles[6] = { image1, image2, image3, image4, image5, image6 };
	cout << "bap" << endl;
	GLenum sides[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
					GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
					GL_TEXTURE_CUBE_MAP_POSITIVE_X,
					GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
					GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
					GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
	};
	GLuint textureid;
	glGenTextures(1, &textureid);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureid);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (int i = 0; i < 6; i++) {
		int width, height;
		GLuint tex = TextureFromFile(cubeTexFiles[i], width, height);
		//GLvoid* texData = nullptr;
		GLubyte *texData = new GLubyte[300 * 300];
		float pixel[3];
		//glReadPixels(0, 0, 300, 300, GL_BGR, GL_UNSIGNED_BYTE, &texData);
		for (int x = 0; i < 300; i++) {
			for (int y = 0; i < 300; i++) {
				glReadPixels(0, 0, 1, 1, GL_BGR, GL_FLOAT, &pixel);
			}
		}
		glTexImage2D(sides[i], 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixel);
	}

	return textureid;
}

void Skybox::update()
{
	// Override texture in Render Component
	renderComponent->textureOverride(m_VBO_texture);
}
