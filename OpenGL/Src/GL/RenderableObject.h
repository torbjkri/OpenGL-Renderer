#pragma once
#include <vector>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"


class RenderableObject
{
public:

	/* Easier for low level application*/
	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;
};

