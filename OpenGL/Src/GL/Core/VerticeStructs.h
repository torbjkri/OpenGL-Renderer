#pragma once

#include <glm/glm.hpp>

struct PositionVertex {
	glm::vec3 position_;
};

struct PositionNormalVertex {
	glm::vec3 position_;
	glm::vec3 normal_;
};

struct PositionTextureNormalVertex {
	glm::vec3 position_;
	glm::vec2 texture_position_;
	glm::vec3 normal_;
};

// TODO : Make typedef instead or something
struct TriangleIndices {
	glm::ivec3 indices_;
};
