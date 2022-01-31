#pragma once

#include "GL/Core/VerticeStructs.h"

#include "GL/Core/VertexArray.h"
#include "GL/Core/VertexBuffer.h"
#include "GL/Core/ElementBuffer.h"

#include "GL/Core/Shader.h"

#include "Material.h"

#include <vector>

namespace WE {
	// TODO: Should Meshes be registered with a resource manager?
	class Mesh
	{
	public:
		VertexArray vao_;

		Mesh(std::vector<PositionNormalVertex>& vertices, std::vector<TriangleIndices>& indices, Material material);
		void Render(Shader* shader, const glm::mat4 projectioview, const glm::mat4 model);

	private:
		VertexBuffer vbo_;
		ElementBuffer ebo_;
		Material material_;
	};

}

