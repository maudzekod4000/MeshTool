#include "VertexArrayObject.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void VertexArrayObject::init()
{
	glGenVertexArrays(1, &id);
}

void VertexArrayObject::bind()
{
	glBindVertexArray(id);
}

void VertexArrayObject::addAttribute(VertexAttribute attribute) const
{
	glVertexAttribPointer(attribute.id, attribute.size, GL_FLOAT, GL_FALSE, attribute.stride * sizeof(float), (void*)(attribute.offset * sizeof(float)));
	glEnableVertexAttribArray(attribute.id);
}
