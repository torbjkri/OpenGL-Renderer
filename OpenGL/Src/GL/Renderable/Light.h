#pragma once
#include "RenderableObject.h"
#include <GL/Core/Shader.h>
#include "ObjectProperties.h"


struct Light : RenderableObject {
	LightProperties properties_;

	Light(Shader shader) : RenderableObject(shader)
	{
		InitRenderData();
	}

	// Set up default render data
	void InitRenderData() override;

	virtual void Bind() const override;
	virtual void Unbind() const override;
};

struct DirectionalLight : Light {
	glm::vec3 direction_;

	DirectionalLight(Shader shader, glm::vec3 direction)
		: Light(shader)
		, direction_(direction)
	{}

};

struct PointLight : Light {
	AttenuationCoefficients attenuation_;

	PointLight(Shader shader)
	: Light(shader)
	{}
};

struct SpotLight : Light {
	AttenuationCoefficients attenuation_;
	float cutoff_ = 0.4f; // ~cos(20)

	SpotLight(Shader shader)
		: Light(shader)
	{ }
};
