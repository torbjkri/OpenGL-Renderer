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
	VertexBuffer(const std::vector<TextureVertex>& vertices);

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
