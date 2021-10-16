#pragma once
#include <glad/glad.h>
#include <vector>

#include "VerticeStructs.h"

class ElementBuffer
{
private:
	// ID reference of Element Buffer Object
	GLuint m_RendererID;

public:
	// Constructor that generates an Element Buffer Object and links it to indices
	ElementBuffer(std::vector<GLuint>& indices);
	ElementBuffer(const std::vector<TriangleIndices>& indices);

	// Delete default constructor
	ElementBuffer() = default;

	// Bind the Element Buffer Object
	void Bind();

	// Unbind the Element Buffer Object
	void Unbind();
};

