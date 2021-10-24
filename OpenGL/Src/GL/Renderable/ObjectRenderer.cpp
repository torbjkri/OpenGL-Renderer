#include "ObjectRenderer.h"

#include "GL/Renderable/Objects.h"

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

void ObjectRenderer::Draw(const Cube& cube, const Light& light, const glm::mat4 projection_view)
{
	cube.Bind();

	cube.shader_.SetUniformMatrix4fv("u_ProjectionView", 1, projection_view);
	cube.shader_.SetUniform3f("u_ViewPos", 1.0f, 1.0f, 1.0f);
	cube.shader_.SetUniform3f("u_LightColor", light.color_.x, light.color_.y, light.color_.z);
	cube.shader_.SetUniform3f("u_LightPosition", light.position_.x, light.position_.y, light.position_.z);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	cube.Unbind();
}
