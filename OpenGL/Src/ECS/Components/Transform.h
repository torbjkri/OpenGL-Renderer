#pragma once

#include <glm/vec3.hpp>

struct TransformState {
	glm::vec3 position_;
	glm::vec3 orientation_;
	glm::vec3 scale_;
};

struct Transform
{
	TransformState curr_state_;
	TransformState prev_state_;
};