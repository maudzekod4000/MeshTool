#pragma once

class Graphics
{
public:
	bool init() const;
	bool loadFunctionDefinitions() const;
	void pollEvents() const;
	~Graphics();
};
