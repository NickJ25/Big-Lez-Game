#include "rt3d.h"
#include "rt3dObjLoader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <chrono>
#include <algorithm>
#include "Menu.h"
#include <GLFW/glfw3.h>
#include "Game.h"
#include "Input.h"

#include "windowGLFW.h"

#include "MainMenu.h"

const static float SCREEN_HEIGHT = 1280;
const static float SCREEN_WIDTH = 720;
int SCREENWIDTH, SCREENHEIGHT;
const static float PREFERED_FPS = 60.0f;


using namespace std;
windowGLFW* window;

//glfw init stuff
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{

	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			Input::keyboard1.keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			Input::keyboard1.keys[key] = false;
		}
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	Input::mouse1.current_Xpos = xPos;
	Input::mouse1.current_Ypos = 720 - yPos;
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button >= 0 && button < 1024)
	{
		if (action == GLFW_PRESS)
		{
			Input::mouse1.buttons[button] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			Input::mouse1.buttons[button] = false;
		}
	}
}

void JoystickCallback(int joy, int event)
{
	if (event == GLFW_CONNECTED)
	{
		cout << "Controller " << joy << " has been connected!" << endl;
	}
	else if (event == GLFW_DISCONNECTED)
	{
		cout << "Controller " << joy << " has been disconnected!" << endl;
	}
}

void ControllerHandle() {
	if (glfwJoystickPresent(GLFW_JOYSTICK_1) == GLFW_TRUE) {
		Input::controller1.connected = true;
		Input::controller1.name = glfwGetJoystickName(GLFW_JOYSTICK_1);
		// Buttons
		int count;
		const unsigned char* btns = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);
		for (int i = 0; i < count; i++) {
			if (btns[i] == GLFW_PRESS)Input::controller1.buttons[i] = true;
			if (btns[i] == GLFW_RELEASE) Input::controller1.buttons[i] = false;
		}
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
		Input::controller1.leftThumb.x = axes[0];
		Input::controller1.leftThumb.y = axes[1];
		Input::controller1.rightThumb.x = axes[2];
		Input::controller1.rightThumb.y = axes[3];
		Input::controller1.triggers.x = axes[4];
		Input::controller1.triggers.y = axes[5];
	}
	else {
		Input::controller1.connected = false;
	}
}


int main(int argc, char *argv[]) {

	//initGlfw();
	window = new windowGLFW(1280, 720, "The Big Lez Game");
	window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	window->setKeyCallback(KeyCallback);
	window->setCursorPosCallback(MouseCallback);
	window->setMouseButtonCallback(MouseButtonCallback);
	window->setJoystickCallback(JoystickCallback);

	// Required on Windows *only* init GLEW to access OpenGL beyond 1.1
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) { // glewInit failed, something is seriously wrong
		std::cout << "glewInit failed, aborting." << endl;
		exit(1);
	}

	
	cout << glGetString(GL_VERSION) << endl;
	cout << "Game Start" << endl;

	Menu menuSystem;

	
	while (!glfwWindowShouldClose(window->getWindow())){
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ControllerHandle();
		menuSystem.updateMenus();
		menuSystem.drawMenus();


		glfwSwapBuffers(window->getWindow());
	}
	glfwTerminate();
	window->~windowGLFW();
	return 0;
}

