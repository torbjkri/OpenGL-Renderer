#pragma once
#include <glad/glad.h>
class VertexBuffer;

class VertexArray
{
public:
	// ID reference for the Vertex Array Object
	GLuint m_RendererID;
	// Constructor that generates a VertexArray ID
	VertexArray();

	// Links a VBO Attribute such as a position or color to the VertexArray
	void LinkAttrib(VertexBuffer& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Binds the VertexArray
	void Bind();
	// Unbinds the VertexArray
	void Unbind();
	// Deletes the VertexArray
	void Delete();
};