#pragma once

#include <glm/vec3.hpp>

struct Material {
	glm::vec3 ambient_ = glm::vec3(1.0, 0.5f, 0.31f);
	glm::vec3 diffuse_ = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::vec3 specular_ = glm::vec3(0.5f, 0.5f, 0.5f);
	float shininiess_ = 32.0f;
};

struct LightProperties {
	glm::vec3 ambient_ = glm::vec3(0.1f);
	glm::vec3 diffuse_ = glm::vec3(0.5f);
	glm::vec3 specular_ = glm::vec3(1.0f);
};
