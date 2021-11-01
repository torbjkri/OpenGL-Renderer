#pragma once

#include <glm/vec3.hpp>

struct Material {
	Texture diffuse_;
	Texture specular_;
	float shininiess_ = 32.0f;
};

struct LightProperties {
	glm::vec3 ambient_ = glm::vec3(0.1f);
	glm::vec3 diffuse_ = glm::vec3(0.5f);
	glm::vec3 specular_ = glm::vec3(1.0f);
};

struct AttenuationCoefficients {
	float constant_ = 1.0f;
	float linear_ = 0.09f;
	float quadratic_ = 0.032f;
};
