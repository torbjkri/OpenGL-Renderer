#include "CubeRenderer.h"
#include <vector>

#include <GL/VertexArray.h>
#include <GL/VertexBuffer.h>
#include <GL/ElementBuffer.h>

CubeRenderer::CubeRenderer(Shader shader)
	: ObjectRenderer(shader)
{
	InitRenderData();
}

void CubeRenderer::Draw(Texture& texture, const glm::mat4 projectionView)
{
	m_Shader.Bind();
	m_VAO.Bind();
	texture.Bind(0);
	m_Shader.SetUniform1i("u_Texture", 0);
	m_Shader.SetUniformMatrix4fv("u_ProjectionView", 1, projectionView);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void CubeRenderer::InitRenderData()
{

    std::vector<TextureVertex> verts = {
        {{1.5f, 1.5f, 0.0f}, {1.0f, 1.0f}},
        {{1.5f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, 1.5f, 0.0f}, {0.0f, 1.0f}},
    };

    std::vector<TriangleIndices> idxs = {
        {{0, 1, 3}},
        {{1, 2, 3}}
    };

	m_VBO = VertexBuffer(verts);
	m_EBO = ElementBuffer(idxs);


	m_VAO.Bind();
	m_VBO.Bind();
	m_EBO.Bind();

	m_VAO.LinkAttrib(m_VBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	m_VAO.LinkAttrib(m_VBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3*sizeof(float)));

	m_VAO.Unbind();
	m_VBO.Unbind();
	m_EBO.Unbind();
}


