#pragma once


#include "glad/glad.h"
#include "GL/VertexArray.h"
#include "GL/ElementBuffer.h"
#include "GL/VertexBuffer.h"
#include "GL/Shader.h"
#include "GL/Texture.h"

#include <glm/glm.hpp>


struct RenderableObject {
	Shader shader_;
	
	VertexArray vao_;
	VertexBuffer vbo_;
	ElementBuffer ebo_;

	glm::vec3 position_ =  glm::vec3(0.0f, 0.0f, 0.0);
	glm::mat4 model_mat_ = glm::mat4(1.0f);
	float scale_ = 1.0f;

	RenderableObject(Shader shader) : shader_(shader) {}
	virtual ~RenderableObject() = default;
	virtual void InitRenderData() = 0;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

};

struct Light : RenderableObject {
	glm::vec3 color_;

	Light(Shader shader, glm::vec4 color) : RenderableObject(shader), color_(color)
	{
		InitRenderData();
	}

	// Set up default render data
	void InitRenderData() override;

	void Bind() const override;
	void Unbind() const override;
};

struct Cube : RenderableObject {
	
	Cube(Shader shader)
		: RenderableObject(shader)
	{}

};

struct ColorCube : Cube {
	glm::vec3 color_;

	ColorCube(Shader shader, glm::vec4 color) : Cube(shader), color_(color)
	{
		InitRenderData();
	}

	// Set up default render data
	void InitRenderData() override;

	void Bind() const override;
	void Unbind() const override;
};

struct TextureCube : Cube {
	Texture texture_;

	TextureCube(Shader shader, Texture texture) : Cube(shader), texture_(texture)
	{
		InitRenderData();
	}

	// Set up default render data
	void InitRenderData() override;

	void Bind() const override;
	void Unbind() const override;
};
