#include "Mesh.h"

#include "GL/Core/VertexArray.h"
#include "GL/Core/VertexBuffer.h"
#include "GL/Core/ElementBuffer.h"
#include "GL/Core/Shader.h"

#include <memory>

#include <glm/vec4.hpp>

#include <GLFW/glfw3.h>

#include <iostream>

Mesh::Mesh(std::vector<PositionVertex>& vertices, std::vector<TriangleIndices>& indices)
{
	vbo_ = VertexBuffer(vertices);
	ebo_ = ElementBuffer(indices);

	vao_.Bind();
	vbo_.Bind();
	ebo_.Bind();

	vao_.LinkAttrib(vbo_, 0, 3, GL_FLOAT, sizeof(PositionVertex), (void*)offsetof(PositionVertex, m_VertexPosition));

	vao_.Unbind();
	vbo_.Unbind();
	ebo_.Unbind();
}

void Mesh::Render(Shader* shader, const glm::mat4 scene_state)
{
	vao_.Bind();
	shader->Bind();
	shader->SetUniform4fv("u_Color", 1, glm::vec4(0.3f, 1.0f, 0.2f, 1.0f));
	shader->SetUniformMatrix4fv("u_ProjectionViewModel", 1, scene_state);
	glDrawElements(GL_TRIANGLES, ebo_.NumElements(), GL_UNSIGNED_INT, 0);
}
