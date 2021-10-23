#pragma once


#include "glad/glad.h"
#include "GL/VertexArray.h"
#include "GL/ElementBuffer.h"
#include "GL/VertexBuffer.h"
#include "GL/Shader.h"
#include "GL/Texture.h"

#include <glm/glm.hpp>



struct Cube {
	VertexArray vao_;
	VertexBuffer vbo_;
	ElementBuffer ebo_;

	Shader shader_;
	Texture texture_;
	
	glm::mat4 model_mat_;
	
	Cube(Shader shader, Texture texture);

	// Set up default render data
	void InitRenderData();

	// Bind properties of the cube
	void Bind() const;

	// Unbind the cube
	void Unbind() const;
};
