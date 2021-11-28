#pragma once

#include <memory>

#include <GLFW/glfw3.h>

#include "GL/Core/Shader.h"
#include "GL/Core/VertexArray.h"
#include "GL/Core/VertexBuffer.h"
#include "GL/Core/ElementBuffer.h"

struct CubeData
{
	VertexArray vao_;
	VertexBuffer vbo_;
	ElementBuffer ebo_;

	CubeData()
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
        vao_.LinkAttrib(vbo_, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        vao_.LinkAttrib(vbo_, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));

        vao_.Unbind();
        vbo_.Unbind();
        ebo_.Unbind();
	}

    void Bind()
    {
        vao_.Bind();
    }
};

struct RenderableCube
{
    glm::vec4 color_;
	std::shared_ptr<CubeData> cube_;
	std::shared_ptr<Shader> shader_;

    void Render()
    {
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
};