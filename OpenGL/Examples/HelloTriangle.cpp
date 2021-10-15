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
    Shader color_shader("Resources\\Shaders\\BasicColor.shader");
    color_shader.SetUniformMatrix4fv("u_ProjectionView", 1, camera.GetProjectionView());
    Shader texture_shader("Resources\\Shaders\\BasicTexture.shader");
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


    std::vector<float> vertices2 = {
         1.5f,  1.5f, 0.0f, 1.0f, 1.0f, // top right
         1.5f,  1.0f, 0.0f, 1.0f, 0.0f, // bottom right
         1.0f,  1.0f, 0.0f, 0.0f, 0.0f, // bottom left
         1.0f,  1.5f, 0.0f, 0.0f, 1.0f // top left 
    };
    std::vector<GLuint> indices2 = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    VertexArray VAO2;
    VAO2.Bind();

    VertexBuffer VBO2(vertices2);
    ElementBuffer EBO2(indices2);

    VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    VAO2.LinkAttrib(VBO2, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3*sizeof(float)));

    VAO2.Unbind();
    VBO2.Unbind();
    EBO2.Unbind();

    Texture smiley = Texture("Resources\\Textures\\wall.jpg");

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
        VAO2.Bind();
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

