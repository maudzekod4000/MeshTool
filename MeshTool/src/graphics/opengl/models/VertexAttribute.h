#pragma once

struct VertexAttribute {
	VertexAttribute(unsigned int id, unsigned int size, unsigned int stride, unsigned int offset) :
		id(id), size(size), stride(stride), offset(offset) {}
	VertexAttribute() {}

	unsigned int id;
	// Number of floating point values per this attribute
	unsigned int size;
	// Number of floating point values per all attributes
	unsigned int stride;
	// Number of float values from the start of vertex attribute array to the first float value of the current attribute.
	unsigned int offset;
};
