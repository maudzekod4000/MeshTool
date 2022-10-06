#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "TypeDefs.h"
#include "Vertex.h"

class Triangle {
public:
	Triangle(Vertex& a, Vertex& b, Vertex& c) : a(a), b(b), c(c) {}
	Triangle() : a(Triangle::defaultVertex), b(Triangle::defaultVertex), c(Triangle::defaultVertex) {}

	Vertex& a;
	Vertex& b;
	Vertex& c;

private:
	static Vertex defaultVertex;
};

#endif // !TRIANGLE_H
