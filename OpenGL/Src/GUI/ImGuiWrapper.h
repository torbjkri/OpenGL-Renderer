#pragma once

struct GLFWwindow;

class ImGuiWrapper
{
public:
	ImGuiWrapper(GLFWwindow * window);
	ImGuiWrapper() = delete;
	ImGuiWrapper(const ImGuiWrapper&) = delete;
	void operator=(const ImGuiWrapper&) = delete;

	~ImGuiWrapper();

	void NewFrame();
	void Render();

};

