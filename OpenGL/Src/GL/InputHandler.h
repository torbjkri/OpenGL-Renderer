#pragma once

#include <GLFW/glfw3.h>
#include <GL/Camera.h>

#include <memory>

class InputHandler
{
private:
	GLFWwindow* m_Window;
	std::shared_ptr<Camera> m_Camera;

public:
	InputHandler(GLFWwindow* window, std::shared_ptr<Camera> cam);
	InputHandler(const InputHandler&) = delete;
	InputHandler operator=(const InputHandler&) = delete;

	void ProcessInput();

private:
	void HandleKeyboard();
	void HandleMouse();
};

