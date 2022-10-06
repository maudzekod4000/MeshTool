#include "GPUBufferLoader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../models/GeometryObject.h"

void GPUBufferLoader::init()
{
	vao.init();
	vao.bind();
	vbo.init(GL_ARRAY_BUFFER);
	vbo.bind();
	ebo.init();
	ebo.bind();
}

void GPUBufferLoader::loadBuffers(const GeometryObject& geometry)
{
	size_t componentCount = geometry.verticesComponents.size();
	float* buffer = new float[componentCount];

	for (int i = 0; i < componentCount; i++) {
		buffer[i] = geometry.verticesComponents[i];
	}

	vbo.fillBuffer(buffer, componentCount);
	delete[] buffer;

	size_t indicesCount = geometry.trianglesIndices.size();
	unsigned int* indices = new unsigned int[indicesCount];

	for (size_t idx = 0; idx < indicesCount; idx++) {
		indices[idx] = geometry.trianglesIndices[idx];
	}

	ebo.fillBuffer(indices, indicesCount * sizeof(unsigned int));
	delete[] indices;

	vao.addAttribute(VertexAttribute{ 0,3,3,0 });
}

void GPUBufferLoader::deinit()
{
}
