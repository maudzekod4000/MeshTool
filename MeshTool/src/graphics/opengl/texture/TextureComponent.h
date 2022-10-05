#pragma once

#include <string>

class TextureComponent
{
public:
	~TextureComponent();
	void init(int textureUnit);
	void load(const std::string& file);
	void bind();

	int textureUnit;
	unsigned int id;
private:
	int width;
	int height;
	int nChannels;
	
	unsigned char* data;
	bool hasAlpha;

	void deinit();
};
