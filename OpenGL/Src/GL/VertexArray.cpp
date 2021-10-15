#include "VertexArray.h"
#include "VertexBuffer.h"

#include <glad/glad.h>
// Constructor that generates a VertexArray m_RendererID
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

// Links a VBO Attribute such as a position or color to the VertexArray
void VertexArray::LinkAttrib(VertexBuffer& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds the VertexArray
void VertexArray::Bind()
{
	glBindVertexArray(m_RendererID);
}

// Unbinds the VertexArray
void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VertexArray
void VertexArray::Delete()
{
	glDeleteVertexArrays(1, &m_RendererID);
}
