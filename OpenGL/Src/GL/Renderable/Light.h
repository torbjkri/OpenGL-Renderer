#pragma once
#include "RenderableObject.h"
#include "GL/Shader.h"
#include "ObjectProperties.h"

struct Light : RenderableObject {
	LightProperties properties_;

	Light(Shader shader) : RenderableObject(shader)
	{
		InitRenderData();
	}

	// Set up default render data
	void InitRenderData() override;

	void Bind() const override;
	void Unbind() const override;
};

