#include "Mesh.h"

#include "GL/Core/VertexArray.h"
#include "GL/Core/VertexBuffer.h"
#include "GL/Core/ElementBuffer.h"
#include "GL/Core/Shader.h"

#include <memory>

#include <glm/glm.hpp>

#include <GLFW/glfw3.h>

#include <iostream>

Mesh::Mesh(std::vector<PositionNormalVertex>& vertices, std::vector<TriangleIndices>& indices, Material material)
	: material_(material)
{
	vbo_ = VertexBuffer(vertices);
	ebo_ = ElementBuffer(indices);

	vao_.Bind();
	vbo_.Bind();
	ebo_.Bind();

	vao_.LinkAttrib(vbo_, 0, 3, GL_FLOAT, sizeof(PositionNormalVertex), (void*)offsetof(PositionNormalVertex, position_));
	vao_.LinkAttrib(vbo_, 1, 3, GL_FLOAT, sizeof(PositionNormalVertex), (void*)offsetof(PositionNormalVertex, normal_));

	vao_.Unbind();
	vbo_.Unbind();
	ebo_.Unbind();
}

void Mesh::Render(Shader* shader, const glm::mat4 projectioview, const glm::mat4 model)
{

	/*
	TODO: CURRENT STATUS: Need light values
	*/

	static int i = 0;
	vao_.Bind();
	material_.Bind(shader);
	shader->Bind();
	shader->SetUniform3f("u_ViewPos", glm::vec3(0.0f, 0.0f, 5.0f));
	shader->SetUniform3f("u_Light.position", glm::vec3(5.0f * glm::cos(glm::radians(360 * static_cast<float>(i++) / 650.0f)), 5.0f * glm::cos(glm::radians(360 * static_cast<float>(i++) / 300.0f)), 5.0f));
	shader->SetUniform3f("u_Light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader->SetUniform3f("u_Light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	shader->SetUniform3f("u_Light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->SetUniformMatrix4fv("u_ProjectionView", 1, projectioview);
	shader->SetUniformMatrix4fv("u_Model", 1, model);
	glDrawElements(GL_TRIANGLES, ebo_.NumElements(), GL_UNSIGNED_INT, 0);
	glFinish();
}
