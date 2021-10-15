#pragma once
#include "RenderableObject.h"

#include "VerticeStructs.h"

class RenderableCube : public RenderableObject
{
public:
	RenderableCube(const std::vector<TextureVertex> &vertices, const std::vector<TriangleIndices>& indices);
	~RenderableCube();

	void Bind() override;
	void Unbind() override;

private:
	VertexArray m_VAO;
	VertexBuffer m_VBO;
	ElementBuffer m_EBO;
};

