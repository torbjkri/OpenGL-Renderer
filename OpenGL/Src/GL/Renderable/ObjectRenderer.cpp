#include "ObjectRenderer.h"

#include "GL/Renderable/Objects.h"

#include "GL/VertexArray.h"
#include "GL/ElementBuffer.h"
#include "GL/VertexBuffer.h"
#include "GL/VerticeStructs.h"
#include "GL/Shader.h"

#include <glm/glm.hpp>

void ObjectRenderer::Draw(const Cube& cube, const glm::mat4 projection_view)
{
	cube.Bind();
	cube.shader_.SetUniformMatrix4fv("u_ProjectionView", 1, projection_view);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	cube.Unbind();
}
