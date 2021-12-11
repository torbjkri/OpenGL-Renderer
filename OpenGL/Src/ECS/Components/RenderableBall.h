#pragma once

#include <memory>
#include <vector>
#include <tuple>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GL/Core/Shader.h"
#include "GL/Core/VertexArray.h"
#include "GL/Core/VertexBuffer.h"
#include "GL/Core/ElementBuffer.h"

#include <glm/glm.hpp>

struct BallData
{
    VertexArray vao_;
    VertexBuffer vbo_;
    ElementBuffer ebo_;

    std::tuple<std::vector<PositionNormalVertex>, std::vector<TriangleIndices>> buildBallVertices2(int subdivision);

    int num_triangles_;

    BallData()
    {
        auto  [verts, idxs] = buildBallVertices2(3);


        vbo_ = VertexBuffer(verts);
        ebo_ = ElementBuffer(idxs);

        num_triangles_ = idxs.size();


        vao_.Bind();
        vbo_.Bind();
        ebo_.Bind();

        vao_.LinkAttrib(vbo_, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
        vao_.LinkAttrib(vbo_, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

        vao_.Unbind();
        vbo_.Unbind();
        ebo_.Unbind();
    }

    void Bind()
    {
        vao_.Bind();
    }

};

struct RenderableBall
{
    glm::vec4 color_;
    std::shared_ptr<BallData> cube_;
    std::shared_ptr<Shader> shader_;

    void Render()
    {
        glDrawElements(GL_TRIANGLES, cube_->num_triangles_ * 3, GL_UNSIGNED_INT, 0);
    }
};