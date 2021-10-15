#pragma once

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GUI/ImGuiWrapper.h"

/*
Display and Context manager class.
Quite simplified interface which can be extended as needed
*/

class GLContext {
private:
	GLFWwindow* m_Window;
	ImGuiWrapper* m_GuiContext;
	bool m_WireframeMode;

	void RenderGui();

public:
	GLContext();
	GLContext(const GLContext&) = delete;
	void operator=(const GLContext&) = delete;

	~GLContext();

	void BeginFrame();
	void EndFrame();

	bool ShouldClose();
	GLFWwindow* GetWindow();

};
