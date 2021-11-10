#include "Light.h"

#include <GL/Core/VertexArray.h>
#include <GL/Core/ElementBuffer.h>
#include <GL/Core/VertexBuffer.h>
#include <GL/Core/VerticeStructs.h>
#include <GL/Core/Shader.h>
#include <GL/Core/Texture.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


void Light::InitRenderData()
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
    };

    std::vector<TriangleIndices> idxs = {
        {{0, 1, 3}},
        {{1, 2, 3}},

        {{0, 4, 1}},
        {{4, 1, 5}},

        {{4, 5, 7}},
        {{5, 6, 7}},

        {{3, 7, 2}},
        {{6, 2, 7}},

        {{0, 3, 7}},
        {{4, 0, 7}},

        {{1, 2, 6}},
        {{5, 6, 1}}
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

void Light::Bind() const
{
	vao_.Bind();
	shader_.Bind();
	shader_.SetUniform3fv("u_LightColor", 1, &properties_.specular_.x);

	glm::mat4 model_mat = glm::translate(glm::mat4(1.0), position_);
	model_mat = model_mat * orientation_mat_;
	model_mat = glm::scale(model_mat, glm::vec3(scale_));

	shader_.SetUniformMatrix4fv("u_Model", 1, model_mat);
}

void Light::Unbind() const
{
	vao_.Unbind();
}
