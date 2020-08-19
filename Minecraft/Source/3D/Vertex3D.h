#pragma once

#include "Vendor/glm/glm.hpp"

namespace MC {
	struct Vertex3D {
		glm::vec3 position;
		glm::vec2 texCoord;
		glm::vec3 normal;
	};
}