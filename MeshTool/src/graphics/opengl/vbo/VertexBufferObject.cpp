#include "VertexBufferObject.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void VertexBufferObject::init(unsigned int glBufferType)
{
	glGenBuffers(1, &id);
	this->glBufferType = glBufferType;
}

void VertexBufferObject::bind()
{
	glBindBuffer(glBufferType, id);
}

void VertexBufferObject::unbind()
{
	glBindBuffer(glBufferType, 0);
}

void VertexBufferObject::fillBuffer(void* data, int size)
{
	glBufferData(glBufferType, size * sizeof(float), data, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &id);
}
