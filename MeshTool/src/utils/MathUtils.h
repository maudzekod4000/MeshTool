#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "../models/TypeDefs.h"

namespace MathUtils {
	inline Vector3D calculateSurfaceGeometricNormal(const Vertex& v1, const Vertex& v2, const Vertex& v3) {
		return glm::normalize(glm::cross(v2 - v1, v3 - v1));
	}
}

#endif // !MATH_UTILS_H
