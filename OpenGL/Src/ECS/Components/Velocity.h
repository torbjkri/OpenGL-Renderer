#pragma once

#include <glm/vec3.hpp>

struct Velocity
{
	glm::vec3 linear_ = glm::vec3(0.0f);
	glm::vec3 angular_ = glm::vec3(0.0);
};