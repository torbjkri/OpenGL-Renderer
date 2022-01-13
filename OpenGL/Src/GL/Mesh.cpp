#include "Mesh.h"

#include "GL/Core/VertexArray.h"
#include "GL/Core/VertexBuffer.h"
#include "GL/Core/ElementBuffer.h"
#include "GL/Core/Shader.h"

#include <memory>

#include <glm/vec4.hpp>

#include <GLFW/glfw3.h>

Mesh::Mesh(std::vector<PositionNormalVertex>& vertices, std::vector<TriangleIndices>& indices)
{
	vbo_ = VertexBuffer(vertices);
	ebo_ = ElementBuffer(indices);

	vao_.Bind();
	vbo_.Bind();
	ebo_.Bind();

	vao_.LinkAttrib(vbo_, 0, 3, GL_FLOAT, sizeof(PositionNormalVertex), (void*)offsetof(PositionNormalVertex, m_VertexPosition));
	vao_.LinkAttrib(vbo_, 1, 3, GL_FLOAT, sizeof(PositionNormalVertex), (void*)offsetof(PositionNormalVertex, m_VertexNormal));

	vao_.Unbind();
	vbo_.Unbind();
	ebo_.Unbind();
}

void Mesh::Render(Shader* shader)
{
	vao_.Bind();
	shader->Bind();
	shader->SetUniform4fv("u_Color", 1, glm::vec4(0.3f, 1.0f, 0.2f, 1.0f));
	glDrawElements(GL_TRIANGLES, ebo_.NumElements(), GL_UNSIGNED_INT, 0);
}
