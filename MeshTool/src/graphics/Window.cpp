#include "Window.h"

#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

bool Window::init(int width, int height, const std::string& label, const Color& clearScreenColor)
{
	this->width = width;
	this->height = height;
	this->clearScreenColor = clearScreenColor;

	window = glfwCreateWindow(width, height, label.c_str(), NULL, NULL);
	
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	return window == nullptr;
}

void Window::makeActive() const
{
	glfwMakeContextCurrent(window);
}

void Window::clear() const
{
	glClearColor(clearScreenColor.r, clearScreenColor.g, clearScreenColor.b, clearScreenColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::close() const
{
	glfwSetWindowShouldClose(window, true);
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(window);
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(window);
}

void Window::disableCursor() const
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow* Window::getRaw() const 
{
	return window;
}

void Window::registerCursorPositionCallback(void* callback)
{
	glfwSetCursorPosCallback(window, static_cast<GLFWcursorposfun>(callback));
}

void Window::registerMouseButtonCallback(void* callback)
{
	glfwSetMouseButtonCallback(window, static_cast<GLFWmousebuttonfun>(callback));
}

void Window::registerScrollCallback(void* callback)
{
	glfwSetScrollCallback(window, static_cast<GLFWscrollfun>(callback));
}

void Window::deinit() const
{
	if (window != nullptr) {
		glfwDestroyWindow(window);
	}
}

Window::~Window()
{
	deinit();
}
