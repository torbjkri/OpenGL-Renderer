#pragma once

#include <glm/vec3.hpp>

struct Gravity
{
	glm::vec3 force_ = glm::vec3(0.0f, -9.81f, 0.0);
};