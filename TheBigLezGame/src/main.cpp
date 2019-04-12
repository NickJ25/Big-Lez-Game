//glew
#include <GL/glew.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//std library
#include <iostream>
#include <chrono>
#include <algorithm>

//GLFW
#include <GLFW/glfw3.h>

//Classes needed to initialise the game
#include "Input.h"
#include "windowGLFW.h"
#include "MainMenu.h"

//static variables
const static float SCREEN_HEIGHT = 1280;
const static float SCREEN_WIDTH = 720;
int SCREENWIDTH, SCREENHEIGHT;
const static float PREFERED_FPS = 60.0f;

using namespace std;

//create a window instance 
windowGLFW* window;

//glfw init stuff
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

//for monitoring time
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

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
	//mouse position control using the universal inputs
	Input::mouse1.current_Xpos = xPos;
	Input::mouse1.current_Ypos = 720 - yPos;
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	//mouse button control using the universal inputs
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
	//debug information to check controller connected/disconnected sucessfully
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
	//using GLFW to set up external controllers
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


int main() {

	//create a window and setup callbacks using GLFW
	window = new windowGLFW(1280, 720, "The Big Lez Game");
	window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	window->setKeyCallback(KeyCallback);
	window->setCursorPosCallback(MouseCallback);
	window->setMouseButtonCallback(MouseButtonCallback);
	window->setJoystickCallback(JoystickCallback);

	//declare universal inputs
	Input::keyboard1.type = Input::KEYBOARD;
	Input::mouse1.type = Input::KEYBOARD;
	Input::controller1.type = Input::CONTROLLER1;
	Input::controller2.type = Input::CONTROLLER2;

	// Initial Screen Size Setup
	Input::SCREEN_HEIGHT = 720;
	Input::SCREEN_WIDTH = 1280;

	// Required on Windows *only* init GLEW to access OpenGL beyond 1.1
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) { // glewInit failed, something is seriously wrong
		std::cout << "glewInit failed, aborting." << endl;
		exit(1);
	}

	//debug info
	//cout << glGetString(GL_VERSION) << endl;
	//cout << "Game Start" << endl;

	//declare a new menu instance
	Menu menuSystem;
	
	while (!glfwWindowShouldClose(window->getWindow())){

		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//reset the screen
		glfwPollEvents();
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//controller update
		ControllerHandle();

		//menu updates
		menuSystem.updateMenus();
		menuSystem.drawMenus();

		//swap frames
		glfwSwapBuffers(window->getWindow());
	}
	//end the scene and program
	glfwTerminate();
	window->~windowGLFW();
	return 0;
}

