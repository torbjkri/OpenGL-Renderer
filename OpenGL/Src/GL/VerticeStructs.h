#pragma once

#include <glm/glm.hpp>


struct PositionVertex {
	glm::vec3 m_VertexPosition;
};

struct TextureVertex {
	glm::vec3 m_VertexPosition;
	glm::vec2 m_TexturePosition;
};

struct TriangleIndices {
	glm::ivec3 m_Indices;
};
