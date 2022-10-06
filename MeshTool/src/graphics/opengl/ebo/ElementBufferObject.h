#pragma once

class ElementBufferObject {
public:
	void init();
	void bind();
	void fillBuffer(void* data, int sizeInBytes);
	~ElementBufferObject();
private:
	unsigned int id;
};