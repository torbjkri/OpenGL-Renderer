#pragma once
#include <vector>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"


class RenderableObject
{
public:
	RenderableObject() = default;
	virtual ~RenderableObject();


	/* Easier for low level application*/
	virtual void Bind();
	virtual void Unbind();
};

