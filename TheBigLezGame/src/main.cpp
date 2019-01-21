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

#include "windowGLFW.h"

#include "MainMenu.h"

const static float SCREEN_HEIGHT = 1280;
const static float SCREEN_WIDTH = 720;
int SCREENWIDTH, SCREENHEIGHT;
const static float PREFERED_FPS = 60.0f;


using namespace std;
windowGLFW* window;

//glfw init stuff
//GLFWwindow *window;
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

#pragma region Old GLFW Code

//// Is called whenever a key is pressed/released via GLFW
//void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
//{
//	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
//	{
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//
//	if (key >= 0 && key < 1024)
//	{
//		if (action == GLFW_PRESS)
//		{
//			keys[key] = true;
//		}
//		else if (action == GLFW_RELEASE)
//		{
//			keys[key] = false;
//		}
//	}
//}
//
//void MouseCallback(GLFWwindow *window, double xPos, double yPos)
//{
//	if (firstMouse)
//	{
//		lastX = xPos;
//		lastY = yPos;
//		firstMouse = false;
//	}
//
//	GLfloat xOffset = xPos - lastX;
//	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
//
//	lastX = xPos;
//	lastY = yPos;
//
//	cout << lastX << " " << lastY << endl;
//}

//int initGlfw()
//{
//	// Init GLFW
//	glfwInit();
//
//	// Set all the required options for GLFW
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//	// Create a GLFWwindow object that we can use for GLFW's functions
//	window = glfwCreateWindow(SCREEN_HEIGHT, SCREEN_WIDTH, "The Big Lez Game", nullptr, nullptr);
//
//	if (nullptr == window)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//
//		return EXIT_FAILURE;
//	}
//
//	glfwMakeContextCurrent(window);
//
//	glfwGetFramebufferSize(window, &SCREENWIDTH, &SCREENHEIGHT);
//
//	// Set the required callback functions
//	glfwSetKeyCallback(window, KeyCallback);
//	glfwSetCursorPosCallback(window, MouseCallback);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//
//
//
//	// GLFW Options
//	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//}

#pragma endregion

int main(int argc, char *argv[]) {

	//initGlfw();
	window = new windowGLFW(1280, 720, "The Big Lez Game");
	window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);

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
	MainMenu::mainWindow = window;

	
	while (!glfwWindowShouldClose(window->getWindow())){
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		menuSystem.updateMenus();
		menuSystem.drawMenus();


		glfwSwapBuffers(window->getWindow());
	}
	glfwTerminate();
	window->~windowGLFW();
	return 0;
}

