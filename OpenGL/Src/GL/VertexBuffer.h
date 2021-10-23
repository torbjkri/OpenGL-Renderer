#pragma once

#include <glad/glad.h>
#include <vector>

#include "VerticeStructs.h"

class VertexBuffer
{
public:
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VertexBuffer() = default;
	VertexBuffer(const std::vector<float> vertices);
	VertexBuffer(const std::vector<PositionVertex>& vertices);
	VertexBuffer(const std::vector<PositionNormalVertex>& vertices);
	VertexBuffer(const std::vector<PositionTextureNormalVertex>& vertices);

	// Binds the VertexBuffer
	void Bind();
	// Unbinds the VertexBuffer
	void Unbind();
	// Deletes the VertexBuffer
	void Delete();

private:
	// Reference ID of the Vertex Buffer Object
	unsigned int m_RendererID;
};
