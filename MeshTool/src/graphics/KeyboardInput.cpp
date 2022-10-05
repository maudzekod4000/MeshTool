#include "KeyboardInput.h"

#include <GLFW/glfw3.h>

void KeyboardInput::init(std::shared_ptr<Window> window)
{
    this->window = window;
}

bool KeyboardInput::isKeyPressed(int keyId) const
{
    return glfwGetKey(window->getRaw(), keyId) == GLFW_PRESS;
}
