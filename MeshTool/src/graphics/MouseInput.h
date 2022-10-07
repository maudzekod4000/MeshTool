#pragma once
#include <functional>

class Window;

class MouseInput {
public:
	void init(Window& window, std::function<void(double, double)> handler);

	static std::function<void(double, double)> handler;
};