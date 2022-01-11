#pragma once

#include <glm/glm.hpp>

// TODO Change naming, dont need vertex at every step
struct PositionVertex {
	glm::vec3 m_VertexPosition;
};

struct PositionNormalVertex {
	glm::vec3 m_VertexPosition;
	glm::vec3 m_VertexNormal;
};

struct PositionTextureNormalVertex {
	glm::vec3 m_VertexPosition;
	glm::vec2 m_TexturePosition;
	glm::vec3 m_VertexNormal;
};

// TODO : Make typedef instead or something
struct TriangleIndices {
	glm::ivec3 m_Indices;
};
