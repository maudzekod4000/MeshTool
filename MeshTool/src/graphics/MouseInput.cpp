#include <iostream>

#include "MouseInput.h"

#include "Window.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void MouseInput::init(Window& window, std::function<void(double, double)> handler)
{
	MouseInput::handler = handler;
	window.registerCursorPositionCallback(mouse_callback);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	MouseInput::handler(xpos, ypos);
}

std::function<void(double, double)> MouseInput::handler;