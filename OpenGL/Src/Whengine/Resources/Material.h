#pragma once

#include <glm/vec3.hpp>
#include "ResourceManager.h"

class Shader;

namespace WE {

	struct  Material : public ManagedResource {
		void Bind(Shader* shader);

		// Base material properties
		glm::vec3 ambient_;
		glm::vec3 diffuse_;
		glm::vec3 specular_;
		float shininess_;
	};

}