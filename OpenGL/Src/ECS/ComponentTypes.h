#pragma once

#include <glm/glm.hpp>
#include <memory>

struct Placeable
{
	glm::vec3 position_;
	glm::vec3 orientation_;
	glm::vec3 scale_;
};


struct RenderableCube
{
	std::shared_ptr<CubeData> cube_;
};