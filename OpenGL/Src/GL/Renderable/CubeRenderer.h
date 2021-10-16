#pragma once
#include "ObjectRenderer.h"

#include <GL/VerticeStructs.h>
#include <GL/Texture.h>
#include <GL/Shader.h>

#include <GL/VertexArray.h>
#include <GL/VertexBuffer.h>
#include <GL/ElementBuffer.h>

#include <glm/glm.hpp>

class CubeRenderer : public ObjectRenderer
{
public:
	CubeRenderer(Shader shader);

	void Draw(Texture& texture, const glm::mat4 projectionView);

private:
	VertexArray m_VAO;
	VertexBuffer m_VBO;
	ElementBuffer m_EBO;

protected:
	void InitRenderData() override;
};

