#include "Graphics.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool Graphics::init() const
{
	int initResult = glfwInit();
	glfwSwapInterval(1); // V-Sync
	return initResult;
}

bool Graphics::loadFunctionDefinitions() const
{
	return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void Graphics::pollEvents() const
{
	glfwPollEvents();
}

Graphics::~Graphics()
{
	glfwTerminate();
}
