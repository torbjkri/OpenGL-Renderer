#pragma once

#include <glm/glm.hpp>


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

struct TriangleIndices {
	glm::ivec3 m_Indices;
};
