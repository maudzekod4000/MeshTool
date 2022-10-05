#include "TextureComponent.h"

#include "../../../libs/stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void TextureComponent::init(int textureUnit)
{

	this->textureUnit = textureUnit;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	stbi_set_flip_vertically_on_load(true);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void TextureComponent::load(const std::string& file)
{
	hasAlpha = file.find(".png") != std::string::npos;
	data = stbi_load(file.c_str(), &width, &height, &nChannels, hasAlpha ? STBI_rgb_alpha : 0);
	
	glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? GL_RGBA : GL_RGB, width, height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	deinit();
}

void TextureComponent::bind()
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, id);
}

void TextureComponent::deinit()
{
	if (data != nullptr) {
		stbi_image_free(data);
		data = nullptr;
	}
}

TextureComponent::~TextureComponent()
{
	deinit();
}
