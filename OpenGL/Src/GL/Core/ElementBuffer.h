#pragma once
#include <glad/glad.h>
#include <vector>

#include <GL/Core/VerticeStructs.h>

/*
	TODO: Stop using internal GL types GLuint etc, it's just messy
*/

class ElementBuffer
{
private:
	// ID reference of Element Buffer Object
	GLuint m_RendererID;
	unsigned int m_NumElements;

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

	unsigned int NumElements();
};

