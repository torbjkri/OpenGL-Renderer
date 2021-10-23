#include "Objects.h"

#include "GL/VertexArray.h"
#include "GL/ElementBuffer.h"
#include "GL/VertexBuffer.h"
#include "GL/VerticeStructs.h"
#include "GL/Shader.h"
#include "GL/Texture.h"


void ColorCube::InitRenderData()
{

    std::vector<PositionVertex> verts = {
        {{ 1.0f,  1.0f,  1.0f}},
        {{ 1.0f, -1.0f,  1.0f}},
        {{-1.0f, -1.0f,  1.0f}},
        {{-1.0f,  1.0f,  1.0f}},

        {{ 1.0f,  1.0f, -1.0f}},
        {{ 1.0f, -1.0f, -1.0f}},
        {{-1.0f, -1.0f, -1.0f}},
        {{-1.0f,  1.0f, -1.0f}},

        {{ 1.0f,  1.0f,  1.0f}},
        {{ 1.0f,  1.0f, -1.0f}},
        {{ 1.0f, -1.0f, -1.0f}},
        {{ 1.0f, -1.0f,  1.0f}},

        {{-1.0f,  1.0f,  1.0f}},
        {{-1.0f,  1.0f, -1.0f}},
        {{-1.0f, -1.0f, -1.0f}},
        {{-1.0f, -1.0f,  1.0f}},

        {{ 1.0f,  1.0f,  1.0f}},
        {{ 1.0f,  1.0f, -1.0f}},
        {{-1.0f,  1.0f, -1.0f}},
        {{-1.0f,  1.0f,  1.0f}},

        {{ 1.0f, -1.0f,  1.0f}},
        {{ 1.0f, -1.0f, -1.0f}},
        {{-1.0f, -1.0f, -1.0f}},
        {{-1.0f, -1.0f,  1.0f}},
    };

    std::vector<TriangleIndices> idxs = {
        {{0, 1, 3}},
        {{1, 2, 3}},

        {{4, 5, 7}},
        {{5, 6, 7}},

        {{8, 9, 11}},
        {{9, 10, 11}},

        {{12, 13, 15}},
        {{13, 14, 15}},

        {{16, 17, 19}},
        {{17, 18, 19}},

        {{20, 21, 23}},
        {{21, 22, 23}}
    };

	vbo_ = VertexBuffer(verts);
	ebo_ = ElementBuffer(idxs);


	vao_.Bind();
	vbo_.Bind();
	ebo_.Bind();

	vao_.LinkAttrib(vbo_, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	vao_.Unbind();
	vbo_.Unbind();
	ebo_.Unbind();
}


void ColorCube::Bind() const
{
	vao_.Bind();
	shader_.Bind();
	shader_.SetUniformMatrix4fv("u_Model", 1, model_mat_);
	shader_.SetUniform4f("u_Color", color_.x, color_.y, color_.z, color_.w);
}

void ColorCube::Unbind() const
{
	vao_.Unbind();
}

void TextureCube::InitRenderData()
{

    std::vector<TextureVertex> verts = {
        {{ 1.0f,  1.0f, 1.0f}, {1.0f, 1.0f}},
        {{ 1.0f, -1.0f, 1.0f}, {1.0f, 0.0f}},
        {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}},
        {{-1.0f,  1.0f, 1.0f}, {0.0f, 1.0f}},

        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 1.0f}},
        {{ 1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}},
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}},
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 1.0f}},

        {{ 1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}},
        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 0.0f}},
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}},
        {{ 1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}},

        {{-1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}},
        {{-1.0f,  1.0f, -1.0f}, {1.0f, 0.0f}},
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}},
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}},

        {{ 1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}},
        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 0.0f}},
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}},
        {{-1.0f,  1.0f,  1.0f}, {0.0f, 1.0f}},

        {{ 1.0f, -1.0f,  1.0f}, {1.0f, 1.0f}},
        {{ 1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}},
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}},
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}},
    };

    std::vector<TriangleIndices> idxs = {
        {{0, 1, 3}},
        {{1, 2, 3}},

        {{4, 5, 7}},
        {{5, 6, 7}},

        {{8, 9, 11}},
        {{9, 10, 11}},

        {{12, 13, 15}},
        {{13, 14, 15}},

        {{16, 17, 19}},
        {{17, 18, 19}},

        {{20, 21, 23}},
        {{21, 22, 23}}
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
}


void TextureCube::Bind() const
{
	vao_.Bind();
	shader_.Bind();
	shader_.SetUniformMatrix4fv("u_Model", 1, model_mat_);
	shader_.SetUniform1i("u_Texture", 0);
	texture_.Bind(0);
}

void TextureCube::Unbind() const
{
	vao_.Unbind();
}
