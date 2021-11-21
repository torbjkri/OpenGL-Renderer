#pragma once
#include <vector>

#include "Cube.h"
#include "Light.h"
#include "Mesh.h"
#include "Model.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <memory>

class ObjectRenderer
{
public: 
	static void Draw(const Light& light, const glm::mat4 projection_view);
	static void Draw(const Cube& cube, const Light& light, const glm::mat4 projection_view, glm::vec3 view_pos);
	static void Draw(const std::unique_ptr<Light>& light, const glm::mat4 projection_view);
	static void Draw(const std::unique_ptr<RenderableObject>& cube, const std::unique_ptr<Light>& light, const glm::mat4 projection_view, glm::vec3 view_pos);
	static void Draw(const Mesh& mesh, const Light& light, const glm::mat4 projection_view, glm::vec3 view_pos);
	static void Draw(const Model& model, const Light& light, const glm::mat4 projection_view, glm::vec3 view_pos);
};

