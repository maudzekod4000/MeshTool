#pragma once

#include "../models/VertexAttribute.h"

/*
* Configuration object for attributes. Makes it easy to switch between attribute configurations
* by first setting up one instance per each set of attributes and then switching between them by calling bind() on the desired instance.
*/
class VertexArrayObject
{
public:
	void init();
	void bind();

	/*
	* id - the unique id associated with attribute. This is the 'location' parameter in the shader.
	* size - how many components/values this attribute has? For example, coordinates in 3D space attribute has 3 values.
	* stride - how many float values is the distance between two consequtive vertex values? If the vertex has just 3D coordinates data per vertex
	*		it will have a stride of 3 times sizeof(float).
	* offset - how many float values we have between the start of the current vertex and the current coordinates.
	*/
	void addAttribute(VertexAttribute attribute) const;
private:
	unsigned int id;
};

