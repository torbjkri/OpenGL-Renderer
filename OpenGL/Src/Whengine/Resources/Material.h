#pragma once

#include <glm/vec3.hpp>

class Shader;

struct  Material {
	void Bind(Shader* shader);

	// Base material properties
	glm::vec3 ambient_;
	glm::vec3 diffuse_;
	glm::vec3 specular_;
	float shininess_;
};