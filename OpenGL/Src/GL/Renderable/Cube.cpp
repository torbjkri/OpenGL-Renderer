#include "Cube.h"

#include "GL/VertexArray.h"
#include "GL/ElementBuffer.h"
#include "GL/VertexBuffer.h"
#include "GL/VerticeStructs.h"
#include "GL/Shader.h"
#include "GL/Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Cube::InitRenderData()
{

    std::vector<PositionTextureNormalVertex> verts = {
        {{ 1.0f,  1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
        {{ 1.0f, -1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{-1.0f,  1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},

        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
        {{ 1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},

        {{ 1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},

        {{-1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
        {{-1.0f,  1.0f, -1.0f}, {1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},

        {{ 1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{-1.0f,  1.0f,  1.0f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},

        {{ 1.0f, -1.0f,  1.0f}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
        {{ 1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}}
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

	vao_.LinkAttrib(vbo_, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao_.LinkAttrib(vbo_, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float)));
	vao_.LinkAttrib(vbo_, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));

	vao_.Unbind();
	vbo_.Unbind();
	ebo_.Unbind();
}


void Cube::Bind() const
{
	vao_.Bind();
	shader_.Bind();
    shader_.SetUniform1f("u_Material.shininess", material_.shininiess_);

	shader_.SetUniform1i("u_Material.diffuse", 0);
	material_.diffuse_.Bind(0);

	shader_.SetUniform1i("u_Material.specular", 1);
	material_.specular_.Bind(1);

	glm::mat4 model_mat = glm::translate(glm::mat4(1.0), position_);
	model_mat = model_mat * orientation_mat_;
	model_mat = glm::scale(model_mat, glm::vec3(scale_));

	shader_.SetUniformMatrix4fv("u_Model", 1, model_mat);

}

void Cube::Unbind() const
{
	vao_.Unbind();
}
