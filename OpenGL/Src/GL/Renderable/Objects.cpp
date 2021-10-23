#include "Objects.h"

#include "GL/VertexArray.h"
#include "GL/ElementBuffer.h"
#include "GL/VertexBuffer.h"
#include "GL/VerticeStructs.h"
#include "GL/Shader.h"
#include "GL/Texture.h"

Cube::Cube(Shader shader, Texture texture)
	: shader_(shader)
	, texture_(texture)
{
	InitRenderData();
}

void Cube::InitRenderData()
{

    std::vector<TextureVertex> verts = {
        {{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f}},
        {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
        {{-0.5f, 0.5f, 0.0f}, {0.0f, 1.0f}},
    };

    std::vector<TriangleIndices> idxs = {
        {{0, 1, 3}},
        {{1, 2, 3}}
    };

	vbo_ = VertexBuffer(verts);
	ebo_ = ElementBuffer(idxs);


	vao_.Bind();
	vbo_.Bind();
	ebo_.Bind();

	vao_.LinkAttrib(vbo_, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	vao_.LinkAttrib(vbo_, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3*sizeof(float)));

	vao_.Unbind();
	vbo_.Unbind();
	ebo_.Unbind();

	model_mat_ = glm::mat4(1.0f);
}

void Cube::Bind() const
{
	vao_.Bind();
	shader_.Bind();
	shader_.SetUniformMatrix4fv("u_Model", 1, model_mat_);
	shader_.SetUniform1i("u_Texture", 0);
	texture_.Bind(0);
}

void Cube::Unbind() const
{
	vao_.Unbind();
}