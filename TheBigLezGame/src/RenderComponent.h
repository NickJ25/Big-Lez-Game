#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>

#include "Shader.h"

// Assimp Includes
#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags

using namespace std;

class RenderComponent {
private:
	///////////////////////////////////////////////
	// Find commmon similarities between Anim and Standard, make a class which does the main task but returns the rest back

	// Object 
	std::vector<GLfloat> verts;
	std::vector<GLfloat> norms;
	std::vector<GLfloat> texCoords;
	std::vector<GLfloat> indices;

	// Object Render Settings
	Shader* m_currentShader;
	GLboolean m_depthMask = GL_TRUE;
	GLenum m_cullMode = GL_BACK;
	string directory;

	GLfloat indexNum;
	void loadObject(const char* mesh_filename);
	void loadAnimObject(const char * mesh_filename);


	
public:
	RenderComponent(const char* mesh_filename) {

	};
	void depthMask(GLboolean mode);
	void cullFace(GLenum mode);
	void changeShader(Shader* newShader);
	void Draw();

};