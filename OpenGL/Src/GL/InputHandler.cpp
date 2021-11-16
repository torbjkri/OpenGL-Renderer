#include "InputHandler.h"

#include <GLFW/glfw3.h>
#include "Camera.h"

#include <ImGui/imgui.h>

#include <memory>

bool firstClick = true;

InputHandler::InputHandler(GLFWwindow* window, std::shared_ptr<Camera> cam)
	: m_Window(window)
	, m_Camera(cam)
{
}

void InputHandler::ProcessInput()
{
	HandleKeyboard();

	ImGuiIO& io = ImGui::GetIO();

	if (!io.WantCaptureMouse)
		HandleMouse();
}

void InputHandler::HandleKeyboard()
{
	// Handles key inputs
	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_Camera->MoveForward();
	}
	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_Camera->StrafeLeft();
	}
	if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_Camera->MoveBackward();	
	}
	if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_Camera->StrafeRight();
	}
	if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_Camera->MoveUp();
	}
	if (glfwGetKey(m_Window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		m_Camera->MoveDown();
	}
	if (glfwGetKey(m_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		m_Camera->SetSpeed(0.4f);
	}
	else if (glfwGetKey(m_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		m_Camera->SetSpeed(0.1f);
	}
}

void InputHandler::HandleMouse()
{
	// Handles mouse inputs
	if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		int width;
		int height;

		glfwGetWindowSize(m_Window, &width, &height);

		if (firstClick)
		{
			glfwSetCursorPos(m_Window, (width / 2), (height / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(m_Window, &mouseX, &mouseY);

		m_Camera->MouseTurn(mouseX, mouseY);


		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(m_Window, (width / 2), (height / 2));

	}
	else if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// ToDo: This runs every frame, should have a shielding
		//	     Preferably mouse and KB IO should be handled by a separate class
		// 
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}
