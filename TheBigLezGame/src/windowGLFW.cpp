#include "windowGLFW.h"

void windowGLFW::checkWindow(GLFWwindow* window)
{
	if (nullptr == m_window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
}

void windowGLFW::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
	glfwSetWindowUserPointer(m_window, this);
}

windowGLFW::windowGLFW(int windowWidth, int windowHeight, const char* windowTitle)
{
	// Init GLFW
	glfwInit();

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	m_window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, nullptr, nullptr);
	checkWindow(m_window);

	glfwMakeContextCurrent(m_window);

	glfwGetFramebufferSize(m_window, NULL, NULL);

	// Set the required callback functions
	//glfwSetKeyCallback(m_window, static_cast<GLFWkeyfun>(glfwGetWindowUserPointer(m_window)));
	//glfwSetKeyCallback(m_window, KeyCallback);
	//glfwSetCursorPosCallback(m_window, MouseCallback);
	//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

windowGLFW::~windowGLFW()
{
	//delete m_window;
}

void windowGLFW::setKeyCallback(GLFWkeyfun function)
{
	glfwSetKeyCallback(m_window, function);
}

void windowGLFW::setCursorPosCallback(GLFWcursorposfun function)
{
	glfwSetCursorPosCallback(m_window, function);
}

void windowGLFW::setMouseButtonCallback(GLFWmousebuttonfun function)
{
	glfwSetMouseButtonCallback(m_window, function);
}

void windowGLFW::setInputMode(int mode, int value)
{
	glfwSetInputMode(m_window, mode, value);
}

void windowGLFW::setJoystickCallback(GLFWjoystickfun function)
{
	glfwSetJoystickCallback(function);
}

bool windowGLFW::checkKey(int key)
{
	bool keyStatus;
	if (keys[key]) {
		keyStatus = true;
	}
	else {
		keyStatus = false;
	}

	return keyStatus;
}

glm::vec2 windowGLFW::getWindowSize()
{
	int width, height;
	glfwGetWindowSize(m_window, &width, &height);
	return glm::vec2(width, height);
}

GLFWwindow * windowGLFW::getWindow()
{
	return m_window;
}