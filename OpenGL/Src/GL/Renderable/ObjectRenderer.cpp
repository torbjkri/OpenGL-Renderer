#include "ObjectRenderer.h"

#include "GL/Renderable/Objects.h"

#include "GL/VertexArray.h"
#include "GL/ElementBuffer.h"
#include "GL/VertexBuffer.h"
#include "GL/VerticeStructs.h"
#include "GL/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void ObjectRenderer::Draw(const Cube& cube, const glm::mat4 projection_view)
{
	cube.Bind();
	glm::mat4 mvp = projection_view;
	mvp = glm::translate(mvp, cube.position_);
	mvp = mvp * cube.model_mat_;
	mvp = glm::scale(mvp, glm::vec3(cube.scale_));

	cube.shader_.SetUniformMatrix4fv("u_ProjectionViewModel", 1, mvp);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	cube.Unbind();
}

void ObjectRenderer::Draw(const Cube& cube, const glm::vec3 light_color, const glm::mat4 projection_view)
{
	cube.Bind();
	glm::mat4 mvp = projection_view;
	mvp = glm::translate(mvp, cube.position_);
	mvp = mvp * cube.model_mat_;
	mvp = glm::scale(mvp, glm::vec3(cube.scale_));

	cube.shader_.SetUniformMatrix4fv("u_ProjectionViewModel", 1, mvp);
	cube.shader_.SetUniform3f("u_LightColor", light_color.x, light_color.y, light_color.z);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	cube.Unbind();
}
