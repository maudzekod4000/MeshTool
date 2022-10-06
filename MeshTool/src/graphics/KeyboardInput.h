#pragma once

#include <memory>

#include "Window.h"

class KeyboardInput
{
public:
	void init(std::shared_ptr<Window> window);
	bool isKeyPressed(int keyId) const;
	bool isKeyReleased(int keyId) const;

private:
	std::shared_ptr<Window> window;
};
