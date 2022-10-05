#pragma once

// TODO: Depending on a high-level module is not great - improve this.
#include "../../engine/models/TypeDefs.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;
};