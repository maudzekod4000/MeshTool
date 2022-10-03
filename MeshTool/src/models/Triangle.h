#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "TypeDefs.h"

struct Triangle {
	Vertex a;
	Vertex b;
	Vertex c;
	Vector3D smoothNormal;

	/// <summary>
	/// The number of geometric normals calculated for this vertex.
	/// Used to get an accumilated average for smooth normal.
	/// </summary>
	unsigned int geometricNormalsCount;
};

#endif // !TRIANGLE_H
