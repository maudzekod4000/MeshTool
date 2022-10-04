#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "../models/TypeDefs.h"
#include "../models/Vertex.h"
#include "../models/Triangle.h"
#include "../../lib/glm/gtx/projection.hpp"

namespace MathUtils {
	inline Vector3D calculateSurfaceGeometricNormal(const Point3D& v1, const Point3D& v2, const Point3D& v3) {
		return glm::normalize(glm::cross(v2 - v1, v3 - v1));
	}

	/// <summary>
	/// Calculate the geometric normal for a triangle which the vertices form.
	/// Accumulate the geometric normal per vertex to get the smooth normal for each vertex.
	/// </summary>
	/// <param name="v1">One of the vertices that form a triangle/plane. Method modifies this parameter.</param>
	/// <param name="v2">One of the vertices that form a triangle/plane. Method modifies this parameter.</param>
	/// <param name="v3">One of the vertices that form a triangle/plane. Method modifies this parameter.</param>
	inline void accumulateSmoothNormal(Vertex& v1, Vertex& v2, Vertex& v3) {
		Vector3D triangleNormal = MathUtils::calculateSurfaceGeometricNormal(v1.position, v2.position, v3.position);

		v1.smoothNormal += triangleNormal;
		v1.smoothNormal = glm::normalize(v1.smoothNormal);

		v2.smoothNormal += triangleNormal;
		v2.smoothNormal = glm::normalize(v2.smoothNormal);

		v3.smoothNormal += triangleNormal;
		v3.smoothNormal = glm::normalize(v3.smoothNormal);
	}

	inline float calculateArea(const Triangle& triangle) {
		Vector3D ab = triangle.b.position - triangle.a.position;
		Vector3D ac = triangle.c.position - triangle.a.position;
		
		return glm::length(glm::cross(ab, ac)) / 2.0f;
	}
}

#endif // !MATH_UTILS_H
