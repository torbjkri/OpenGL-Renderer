#pragma once

#include "GL/Core/VerticeStructs.h"

#include "GL/Core/VertexArray.h"
#include "GL/Core/VertexBuffer.h"
#include "GL/Core/ElementBuffer.h"

#include "GL/Core/Shader.h"

#include <vector>


// TODO: Should Meshes be registered with a resource manager?
class Mesh
{
public:
	VertexArray vao_;

	Mesh(std::vector<PositionVertex>& vertices, std::vector<TriangleIndices>& indices);
	void Render(Shader* shader, const glm::mat4 scene_state);

private:
	VertexBuffer vbo_;
	ElementBuffer ebo_;
};

