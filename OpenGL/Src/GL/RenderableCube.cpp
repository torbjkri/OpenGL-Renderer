#include "RenderableCube.h"
#include <vector>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"

RenderableCube::RenderableCube(const std::vector<TextureVertex>& vertices, const std::vector<TriangleIndices>& indices)
	: m_VBO(vertices)
	, m_EBO(indices)
{
	m_VAO.Bind();
	m_VBO.Bind();
	m_EBO.Bind();

	m_VAO.LinkAttrib(m_VBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	m_VAO.LinkAttrib(m_VBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3*sizeof(float)));

	m_VAO.Unbind();
	m_VBO.Unbind();
	m_EBO.Unbind();
}

void RenderableCube::Bind() const
{
	m_VAO.Bind();
}

void RenderableCube::Unbind() const
{
	m_VAO.Unbind();
}
