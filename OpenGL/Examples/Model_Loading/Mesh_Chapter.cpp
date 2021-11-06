
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
#include <GL/Renderable/Cube.h>
#include <GL/Renderable/Light.h>

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


int Mesh_Chapter()
{
    GLContext context; // This must be called at the start of every application


    Camera camera(context.GetWindow());

    ResourceManager::GetInstance()->LoadShader("Resources/Shaders/Lighting/BasicShader.glsl", "basic");
     
      
    Light light(ResourceManager::GetInstance()->GetShader("light"));
    light.position_ = glm::vec3(5.0f, 5.0f, -5.0f);
    light.scale_ = 0.3f;

    Model model("Resource/Models/backpack");


    bool drawRectangle = true;

    while (!context.ShouldClose())
    {

        context.BeginFrame();
        camera.ProcessInput(context.GetWindow());

        light.position_ = glm::vec3(5.0f * glm::cos(glfwGetTime() / 1.0f), 5.0f,  5.0f * glm::sin(glfwGetTime() / 1.0f));


        ObjectRenderer::Draw(model, light, camera.GetProjectionView(), camera.GetPosition());
        ObjectRenderer::Draw(light, camera.GetProjectionView());


        ImGui::Begin("My Window");
        ImGui::Text("Hello ImGui");
        ImGui::Checkbox("Draw Rectangle", &drawRectangle);
        ImGui::ColorEdit3("Color", &light.properties_.specular_.x);
        ImGui::End();

        context.EndFrame();

    }


    exit(EXIT_SUCCESS);
}

