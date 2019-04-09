#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <stack>

#include "Shader.h"
#include "Model.h"
#include "AnimModel.h"

// Assimp Includes
#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags

using namespace std;

class RenderComponent {
private:
	///////////////////////////////////////////////
	// Find commmon similarities between Anim and Standard, make a class which does the main task but returns the rest back


	// Object Settings
	bool m_isAnimated = false;

	Model* testModel; // TEST
	AnimModel* m_objModel;

	// Object Render Settings
	Shader* m_currentShader;
	GLboolean m_depthMask = GL_TRUE;
	GLenum m_cullMode = GL_BACK;
	GLuint m_overrideTexture; // Override texture before draw
	
	//string directory;
	
	// Object Transformations
	glm::mat4 projection;
	glm::mat4 m_view;
	glm::mat4 m_model;

	

	//GLfloat indexNum;
	void loadObject(const char* mesh_filename);
	void loadAnimObject(const char * mesh_filename);

	bool still = false;
	
public:
	RenderComponent(const char* mesh_filename) {
		loadObject(mesh_filename); // TEST
		projection = (glm::perspective(float(glm::radians(60.0f)), 1280.0f / 720.0f, 1.0f, 150.0f));
	};
	void depthMask(GLboolean mode);
	void cullFace(GLenum mode);
	void setView(glm::mat4 view);
	void setDrawMatrix(glm::mat4 matrix);
	void textureOverride(GLuint textureID);
	void changeShader(Shader* newShader);
	void setAnim(float s, float e);
	void setPaused(bool p);
	bool getPaused();
	void setStill(bool s);
	void Draw();
	void setPauseFrame(float p);
};