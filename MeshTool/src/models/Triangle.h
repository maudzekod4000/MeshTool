#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "TypeDefs.h"
#include "../utils/MathUtils.h"

class Triangle {
public:
	Triangle(Vertex& a, Vertex& b, Vertex& c) : a(a), b(b), c(c) {}

	Vertex& a;
	Vertex& b;
	Vertex& c;
};

#endif // !TRIANGLE_H
