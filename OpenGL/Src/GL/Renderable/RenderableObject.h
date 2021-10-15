#pragma once
#include <vector>

#include <GL/VertexArray.h>
#include <GL/VertexBuffer.h>
#include <GL/ElementBuffer.h>


class RenderableObject
{
public:

	/* Easier for low level application*/
	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;
};

