#pragma once
#include <vector>

#include "Objects.h"

#include <glm/mat4x4.hpp>

struct Cube;

class ObjectRenderer
{
public: 
	static void Draw(const Light& cube, const glm::mat4 projection_view);
	static void Draw(const Cube& cube, const glm::mat4 projection_view);
	static void Draw(const Cube& cube, const Light& light, const glm::mat4 projection_view);
};

