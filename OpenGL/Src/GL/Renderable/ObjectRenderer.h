#pragma once
#include <vector>

#include "Cube.h"
#include "Light.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class ObjectRenderer
{
public: 
	static void Draw(const Light& light, const glm::mat4 projection_view);
	static void Draw(const Cube& cube, const Light& light, const glm::mat4 projection_view, glm::vec3 view_pos);
};

