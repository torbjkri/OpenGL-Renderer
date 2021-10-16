#include "GUI/ImGuiWrapper.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "GL/GLContext.h"
#include "GL/Shader.h"
#include "GL/VertexArray.h"
#include "GL/ElementBuffer.h"
#include "GL/VertexBuffer.h"

#include <GL/Camera.h>

#include <GL/Texture.h>

#include <GL/Renderable/RenderableObject.h>
#include <GL/Renderable/RenderableCube.h>

#include <GL/VerticeStructs.h>

#include <GL/ResourceManager.h>


/*
First example
Most of the basic pieces are in place.

Context
    - Create GLFW windowing context
    - start glad
    - Create ImGui rendering context
    - For now it context controls the rendering loop
      requiring to call BeginFrame and EndFrame at each end.
      

VAO, VBO, EBO, take in data, bind and unbind

Shader
    - Take in project relative path and compile vertex and fragment shaders
    - Basic structure of setting uniforms is in place

*/


int HelloTriangle()
{
    GLContext context; // This must be called at the start of every application


    Camera camera(context.GetWindow());

    ResourceManager::GetInstance()->LoadShader("Resources\\Shaders\\BasicColor.shader", "color");
    ResourceManager::GetInstance()->LoadShader("Resources\\Shaders\\BasicTexture.shader", "texture");
    ResourceManager::GetInstance()->LoadTexture("Resources\\Textures\\wall.jpg", "wall");

    Shader color_shader = ResourceManager::GetInstance()->GetShader("color");
    color_shader.SetUniformMatrix4fv("u_ProjectionView", 1, camera.GetProjectionView());

    Shader texture_shader = ResourceManager::GetInstance()->GetShader("texture");
    texture_shader.SetUniformMatrix4fv("u_ProjectionView", 1, camera.GetProjectionView());

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    std::vector<float> vertices = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    std::vector<GLuint> indices = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    VertexArray VAO;
    VAO.Bind();

    VertexBuffer VBO(vertices);
    ElementBuffer EBO(indices);

    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();


    std::vector<TextureVertex> verts = {
        {{1.5f, 1.5f, 0.0f}, {1.0f, 1.0f}},
        {{1.5f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{1.0f, 1.5f, 0.0f}, {0.0f, 1.0f}},
    };

    std::vector<TriangleIndices> idxs = {
        {{0, 1, 3}},
        {{1, 2, 3}}
    };


    RenderableCube cube(verts, idxs);

    ResourceManager::GetInstance()->LoadTexture("Resources\\Textures\\wall.jpg", "wall");

    Texture smiley = ResourceManager::GetInstance()->GetTexture("wall");

    bool drawRectangle = true;

    float size = 1.0f;
    float color[4] = { 0.5f, 0.5f, 0.5f, 1.0f };

    while (!context.ShouldClose())
    {

        context.BeginFrame();

        camera.ProcessInput(context.GetWindow());

        color_shader.Bind();
        VAO.Bind();
        color_shader.SetUniform1f("u_Size", size);
        color_shader.SetUniform4fv("u_Color", 1, color);
        color_shader.SetUniformMatrix4fv("u_ProjectionView", 1, camera.GetProjectionView());
        if (drawRectangle)
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        texture_shader.Bind();
        cube.Bind();
        smiley.Bind(0);
        texture_shader.SetUniform1i("u_Texture", 0);
        texture_shader.SetUniformMatrix4fv("u_ProjectionView", 1, camera.GetProjectionView());

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        ImGui::Begin("My Window");
        ImGui::Text("Hello ImGui");
        ImGui::Checkbox("Draw Rectangle", &drawRectangle);
        ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
        ImGui::ColorEdit4("Color", color);
        ImGui::End();

        context.EndFrame();

    }


    exit(EXIT_SUCCESS);
}

