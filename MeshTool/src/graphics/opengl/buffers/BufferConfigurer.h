#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../opengl/vbo/VertexBufferObject.h"
#include "../../opengl/vao/VertexArrayObject.h"
#include "../../opengl/ebo/ElementBufferObject.h"
#include "../models/VertexAttribute.h"
#include "../../engine/models/serialisation/BufferSerialiser.h"

/* Sets up buffers for shapes/objects */
class BufferConfigurer
{
public:
	void init(
		std::vector<VertexAttribute> attributes,
		std::shared_ptr<BufferSerialiser> serialisation
	);

	void activate();

	void loadBuffer();

	void deactivate();

	~BufferConfigurer();
protected:
	VertexArrayObject vao;
	VertexBufferObject vbo;
	ElementBufferObject ebo;
	std::shared_ptr<BufferSerialiser> serialisation;
};
