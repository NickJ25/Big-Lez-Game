#pragma once
#include "SOIL2/SOIL2.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

using namespace std;

GLint TextureFromFile(const char * path);
GLint TextureFromFile(const char * path, int &width, int &height);
