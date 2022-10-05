#pragma once

class VertexBufferObject {
public:
	void init(unsigned int glBufferType);
	void bind();
	void unbind();
	void fillBuffer(void* data, int size);

	~VertexBufferObject();
private:
	unsigned int id;
	unsigned int glBufferType;
};