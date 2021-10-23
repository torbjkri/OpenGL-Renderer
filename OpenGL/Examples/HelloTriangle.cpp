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

#include <GL/Renderable/ObjectRenderer.h>
#include <GL/Renderable/Objects.h>

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
   
    Cube cube(ResourceManager::GetInstance()->GetShader("texture"), ResourceManager::GetInstance()->GetTexture("wall"));


    bool drawRectangle = true;

    float size = 1.0f;
    float color[4] = { 0.5f, 0.5f, 0.5f, 1.0f };

    while (!context.ShouldClose())
    {

        context.BeginFrame();

        camera.ProcessInput(context.GetWindow());


        ObjectRenderer::Draw(cube, camera.GetProjectionView());


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

