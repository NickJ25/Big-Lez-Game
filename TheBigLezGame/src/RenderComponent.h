#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>
class RenderComponent {
private:
	// Object 
	std::vector<GLfloat> verts;
	std::vector<GLfloat> norms;
	std::vector<GLfloat> texCoords;
	std::vector<GLfloat> indices;
	GLfloat indexNum;
	void loadObject(const char* mesh_filename);
public:
	RenderComponent(const char* mesh_filename) {

	};
	void Draw();

};