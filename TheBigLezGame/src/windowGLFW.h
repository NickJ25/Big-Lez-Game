#pragma once
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"
#include <iostream>

class windowGLFW {
private:
	GLFWwindow *m_window;
	bool keys[1024];
	void checkWindow(GLFWwindow* window);

	void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);


public:
	windowGLFW(int windowWidth, int windowHeight, const char* windowTitle);
	~windowGLFW();

	void setKeyCallback(GLFWkeyfun function);
	void setCursorPosCallback(GLFWcursorposfun function);
	void setMouseButtonCallback(GLFWmousebuttonfun function);
	void setInputMode(int mode, int value);

	bool checkKey(int key);
	glm::vec2 getWindowSize();

	GLFWwindow* getWindow();

};