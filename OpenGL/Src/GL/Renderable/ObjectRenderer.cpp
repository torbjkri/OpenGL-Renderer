#include "ObjectRenderer.h"

#include "GL/Renderable/Cube.h"
#include "GL/Renderable/Light.h"
#include "GL/Renderable/Mesh.h"
#include "GL/Renderable/Model.h"

#include "GL/VertexArray.h"
#include "GL/ElementBuffer.h"
#include "GL/VertexBuffer.h"
#include "GL/VerticeStructs.h"
#include "GL/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void ObjectRenderer::Draw(const Light& light, const glm::mat4 projection_view)
{
	light.Bind();

	light.shader_.SetUniformMatrix4fv("u_ProjectionView", 1, projection_view);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	light.Unbind();
}

void ObjectRenderer::Draw(const Cube& cube, const Light& light, const glm::mat4 projection_view, glm::vec3 view_pos)
{
	cube.Bind();
	cube.shader_.SetUniformMatrix4fv("u_ProjectionView", 1, projection_view);
	cube.shader_.SetUniform3fv("u_ViewPos", 1, &view_pos.x);
	cube.shader_.SetUniform3f("u_LightPosition", light.position_.x, light.position_.y, light.position_.z);

	cube.shader_.SetUniform3fv("u_Light.position", 1, &light.position_.x);
	cube.shader_.SetUniform3fv("u_Light.ambient", 1, &light.properties_.ambient_.x);
	cube.shader_.SetUniform3fv("u_Light.diffuse", 1, &light.properties_.diffuse_.x);
	cube.shader_.SetUniform3fv("u_Light.specular", 1, &light.properties_.specular_.x);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	cube.Unbind();
}

void ObjectRenderer::Draw(const Mesh& mesh, const Light& light, const glm::mat4 projection_view, glm::vec3 view_pos)
{
	mesh.Bind();
	mesh.shader_.SetUniformMatrix4fv("u_ProjectionView", 1, projection_view);
	mesh.shader_.SetUniform3fv("u_ViewPos", 1, &view_pos.x);
	mesh.shader_.SetUniform3f("u_LightPosition", light.position_.x, light.position_.y, light.position_.z);

	mesh.shader_.SetUniform3fv("u_Light.position", 1, &light.position_.x);
	mesh.shader_.SetUniform3fv("u_Light.ambient", 1, &light.properties_.ambient_.x);
	mesh.shader_.SetUniform3fv("u_Light.diffuse", 1, &light.properties_.diffuse_.x);
	mesh.shader_.SetUniform3fv("u_Light.specular", 1, &light.properties_.specular_.x);

	glDrawElements(GL_TRIANGLES, mesh.vertices_.size(), GL_UNSIGNED_INT, 0);
	mesh.Unbind();
}

void ObjectRenderer::Draw(const Model& model, const Light& light, const glm::mat4 projection_view, glm::vec3 view_pos)
{
	for (auto& mesh : model.meshes_) {
		Draw(mesh, light, projection_view, view_pos);
	}
}
