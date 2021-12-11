#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

struct TransformState {
	glm::vec3 position_;
	glm::vec3 orientation_;
	glm::vec3 scale_;
};

struct Transform
{
	TransformState curr_state_;
	TransformState prev_state_;
	glm::mat4 CreateModelMatrix()
	{
		glm::mat4 R(1.0f);
		R = glm::translate(R, curr_state_.position_);
		R = glm::rotate(R, glm::radians(curr_state_.orientation_.x), glm::vec3(1.0f, 0.0f, 0.0f));
		R = glm::rotate(R, glm::radians(curr_state_.orientation_.y), glm::vec3(0.0f, 1.0f, 0.0f));
		R = glm::rotate(R, glm::radians(curr_state_.orientation_.z), glm::vec3(0.0f, 0.0f, 1.0f));
		R = glm::scale(R, curr_state_.scale_);

		return R;
	}
};