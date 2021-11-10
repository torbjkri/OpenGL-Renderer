#pragma once
#include "RenderableObject.h"
#include "ObjectProperties.h"

#include <GL/Core/Texture.h>
#include <GL/core/Shader.h>

struct Cube : RenderableObject {
	Material material_;

	Cube(Shader shader, Texture diffuse, Texture specular) : RenderableObject(shader)
	{
		material_.diffuse_ = diffuse;
		material_.specular_ = specular;
		InitRenderData();
	}

	// Set up default render data
	void InitRenderData() override;

	void Bind() const override;
	void Unbind() const override;
};

