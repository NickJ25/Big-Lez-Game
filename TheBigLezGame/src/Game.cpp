#include "Game.h"
#define DEG_TO_RADIAN 0.017453293


GLuint meshObjects[1];
GLuint textures[1];
GLuint skybox[5];
GLuint cubeIndexCount;
GLfloat r = 0.0f;

// Attenuation Parameters
GLfloat f_att_c = 1.0f;
GLfloat f_att_l = 0.0f;
GLfloat f_att_q = 0.01f;

// Camera Properties
glm::vec3 eye(0.0f, 1.0f, 3.0f);
glm::vec3 at(0.0f, 1.0f, 2.0f);
glm::vec3 up(0.0f, 1.0f, 0.0f);

stack<glm::mat4> mvStack;

GLuint toonProgram;
GLuint skyboxProgram;

rt3d::lightStruct light0 = {
	{1.0f, 1.0f, 1.0f, 1.0f}, // ambient
	{1.0f, 1.0f, 1.0f, 1.0f}, // diffuse
	{1.0f, 1.0f, 1.0f, 1.0f}, // specular
	{-10.0f, 10.0f, 10.0f, 1.0f}  // position
};
glm::vec4 lightPos(-7.0f, 3.6f, -7.5f, 1.0f); //light position

rt3d::materialStruct material0 = {
	{0.0f, 0.8f, 0.2f, 1.0f}, // ambient
	{0.5f, 1.0f, 0.5f, 1.0f}, // diffuse
	{0.0f, 0.1f, 0.0f, 1.0f}, // specular
	2.0f  // shininess
};

// A simple texture loading function
// lots of room for improvement - and better error checking!
GLuint loadBitmap(char *fname) {
	GLuint texID;
	glGenTextures(1, &texID); // generate texture ID

	// load file - using core SDL library
	SDL_Surface *tmpSurface;
	tmpSurface = SDL_LoadBMP(fname);
	if (!tmpSurface) {
		std::cout << "Error loading bitmap" << std::endl;
	}

	// bind texture and set parameters
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	SDL_PixelFormat *format = tmpSurface->format;

	GLuint externalFormat, internalFormat;
	if (format->Amask) {
		internalFormat = GL_RGBA;
		externalFormat = (format->Rmask < format->Bmask) ? GL_RGBA : GL_BGRA;
	}
	else {
		internalFormat = GL_RGB;
		externalFormat = (format->Rmask < format->Bmask) ? GL_RGB : GL_BGR;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, tmpSurface->w, tmpSurface->h, 0,
		externalFormat, GL_UNSIGNED_BYTE, tmpSurface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(tmpSurface); // texture loaded, free the temporary buffer
	return texID;	// return value of texture ID
}

GLuint loadCubeMap(const char*fname[6], GLuint *texID)
{
	glGenTextures(1, texID); // generate texture ID
	GLenum sides[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
						GL_TEXTURE_CUBE_MAP_POSITIVE_X,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
						GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
	};
	SDL_Surface *tmpsurface;

	glBindTexture(GL_TEXTURE_CUBE_MAP, *texID); // bind texture and set parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (int i = 0; i < 6; i++)
	{
		// loadfile - using core SDL Library
		tmpsurface = SDL_LoadBMP(fname[i]);
		if (!tmpsurface)
		{
			std::cout << "Cubemap: Error loading bitmap" << std::endl;
			return *texID;
		}

		glTexImage2D(sides[i], 0, GL_RGB, tmpsurface->w, tmpsurface->h, 0, GL_BGR, GL_UNSIGNED_BYTE, tmpsurface->pixels);
		//texture oaded, free the temporary buffer
		SDL_FreeSurface(tmpsurface);
	}
	return *texID; // return value of texture ID, redundant really
}


void Game::init()
{
	std::cout << "Game Startvvvv" << std::endl;
	// Toon Shader Program
	toonProgram = rt3d::initShaders("src/toonShader.vert", "src/toonShader.frag");
	rt3d::setLight(toonProgram, light0);
	rt3d::setMaterial(toonProgram, material0);
	GLuint uniformIndex = glGetUniformLocation(toonProgram, "in_Constant");
	glUniform1f(uniformIndex, f_att_c);
	uniformIndex = glGetUniformLocation(toonProgram, "in_Linear");
	glUniform1f(uniformIndex, f_att_l);
	uniformIndex = glGetUniformLocation(toonProgram, "in_Quadratic");
	glUniform1f(uniformIndex, f_att_q);

	// Skybox Shader Program
	skyboxProgram = rt3d::initShaders("src/skyboxShader.vert", "src/skyboxShader.frag");

	// Load Skybox
	const char *cubeTexFiles[6] = {
		"assets/Skybox/skyrender_left.bmp", "assets/Skybox/skyrender_front.bmp",
		"assets/Skybox/skyrender_right.bmp", "assets/Skybox/skyrender_back.bmp",
		"assets/Skybox/skyrender_top.bmp", "assets/Skybox/skyrender_bottom.bmp"
	};
	loadCubeMap(cubeTexFiles, &skybox[0]);

	vector<GLfloat> verts;
	vector<GLfloat> norms;
	vector<GLfloat> tex_coords;
	vector<GLuint> indices;

	rt3d::loadObj("assets/cube.obj", verts, norms, tex_coords, indices);
	cubeIndexCount = indices.size();
	meshObjects[0] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), cubeIndexCount, indices.data());

	textures[0] = loadBitmap("assets/test.bmp");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d) {
	return glm::vec3(pos.x + d * std::sin(r*DEG_TO_RADIAN), pos.y, pos.z - d * std::cos(r*DEG_TO_RADIAN));
}

glm::vec3 moveRight(glm::vec3 pos, GLfloat angle, GLfloat d) {
	return glm::vec3(pos.x + d * std::cos(r*DEG_TO_RADIAN), pos.y, pos.z + d * std::sin(r*DEG_TO_RADIAN));
}

void Game::update()
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W]) eye = moveForward(eye, r, 0.1f);
	if (keys[SDL_SCANCODE_S]) eye = moveForward(eye, r, -0.1f);
	if (keys[SDL_SCANCODE_A]) eye = moveRight(eye, r, -0.1f);
	if (keys[SDL_SCANCODE_D]) eye = moveRight(eye, r, 0.1f);
	if (keys[SDL_SCANCODE_Y]) lightPos[2] -= 0.2;//eye = moveForward(eye, r, 0.1f);
	if (keys[SDL_SCANCODE_H]) lightPos[2] += 0.2;
	if (keys[SDL_SCANCODE_G]) lightPos[0] -= 0.2;
	if (keys[SDL_SCANCODE_J]) lightPos[0] += 0.2;
	if (keys[SDL_SCANCODE_I]) lightPos[1] += 0.2;
	if (keys[SDL_SCANCODE_K]) lightPos[1] -= 0.2;
	if (keys[SDL_SCANCODE_R]) eye.y += 0.1;
	if (keys[SDL_SCANCODE_F]) eye.y -= 0.1;

	if (keys[SDL_SCANCODE_COMMA]) r -= 1.0f;
	if (keys[SDL_SCANCODE_PERIOD]) r += 1.0f;
}

void Game::draw()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glUseProgram(toonProgram);
	glm::mat4 projection(1.0);
	projection = glm::perspective(float(60.0f*DEG_TO_RADIAN), 800.0f / 600.0f, 1.0f, 150.0f);
	rt3d::setUniformMatrix4fv(toonProgram, "projection", glm::value_ptr(projection));

	GLfloat scale(1.0f);

	glm::mat4 modelview(1.0);
	mvStack.push(modelview);

	at = moveForward(eye, r, 1.0f);
	mvStack.top() = glm::lookAt(eye, at, up);

	glUseProgram(skyboxProgram);
	rt3d::setUniformMatrix4fv(skyboxProgram, "projection", glm::value_ptr(projection));

	glDepthMask(GL_FALSE); // make sure writing to update depth test is off
	glm::mat3 mvRotOnlyMat3 = glm::mat3(mvStack.top());
	mvStack.push(glm::mat4(mvRotOnlyMat3));
	glCullFace(GL_FRONT); // drawing inside of cube!

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox[0]);
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(1.5f, 1.5f, 1.5f));
	rt3d::setUniformMatrix4fv(skyboxProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::drawIndexedMesh(meshObjects[0], cubeIndexCount, GL_TRIANGLES);
	mvStack.pop();
	glCullFace(GL_BACK);

	// back to remainder of rendering
	glDepthMask(GL_TRUE); // make sure depth test is on

	glUseProgram(toonProgram);

	glm::vec4 tmp = mvStack.top()*lightPos;
	light0.position[0] = tmp.x;
	light0.position[1] = tmp.y;
	light0.position[2] = tmp.z;
	rt3d::setLightPos(toonProgram, glm::value_ptr(tmp));

	rt3d::setUniformMatrix4fv(toonProgram, "projection", glm::value_ptr(projection));

	// draw a cube for ground plane
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(0.0f, 0.1f, 0.0f));
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(5.0f, 0.1f, 5.0f));
	rt3d::setUniformMatrix4fv(toonProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::setMaterial(toonProgram, material0);
	rt3d::drawIndexedMesh(meshObjects[0], cubeIndexCount, GL_TRIANGLES);
	mvStack.pop();

	// draw a cube for light
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(lightPos[0], lightPos[1], lightPos[2]));
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(1.0f, 1.0f, 1.0f));
	rt3d::setUniformMatrix4fv(toonProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::setMaterial(toonProgram, material0);
	rt3d::drawIndexedMesh(meshObjects[0], cubeIndexCount, GL_TRIANGLES);
	mvStack.pop();


	mvStack.pop(); // initial matrix
	glDepthMask(GL_TRUE);
}
