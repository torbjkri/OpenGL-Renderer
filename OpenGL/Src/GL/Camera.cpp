#include "Camera.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include <iostream>

constexpr float NEAR_PLANE = 0.1f;
constexpr float FAR_PLANE = 100.0f;
constexpr float FOV = 80.0f;

Camera::Camera(GLFWwindow *window)
{
	glfwGetWindowSize(window, &m_Width, &m_Height);
	m_Position = glm::vec3(0.0f, 0.0f, 2.0f);
}

glm::mat4 Camera::GetProjectionView() const
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
	projection = glm::perspective(glm::radians(FOV), (float)m_Width / m_Height, NEAR_PLANE, FAR_PLANE);

	return projection * view;
}

glm::vec3 Camera::GetPosition() const
{
	return m_Position;
}

void Camera::MoveForward()
{
	m_Position += m_Speed * m_Orientation;
}

void Camera::MoveBackward()
{
	m_Position += m_Speed * -m_Orientation;
}

void Camera::MoveUp()
{
	m_Position += m_Speed * m_Up;
}

void Camera::MoveDown()
{
	m_Position += m_Speed * -m_Up;
}

void Camera::StrafeLeft()
{
	m_Position += m_Speed * -glm::normalize(glm::cross(m_Orientation, m_Up));
}

void Camera::StrafeRight()
{
	m_Position += m_Speed * glm::normalize(glm::cross(m_Orientation, m_Up));
}

void Camera::SetSpeed(const float speed)
{
	m_Speed = speed;
}

void Camera::MouseTurn(const int mouseX, const int mouseY)
{
	// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
	float rotX = m_Sensitivity * (float)(mouseY - (m_Height / 2)) / m_Height;
	float rotY = m_Sensitivity * (float)(mouseX - (m_Width / 2)) / m_Width;

	// Calculates upcoming vertical change in the Orientation
	glm::vec3 newOrientation = glm::rotate(m_Orientation, glm::radians(-rotX), glm::normalize(glm::cross(m_Orientation, m_Up)));

	// Decides whether or not the next vertical Orientation is legal or not
	if (abs(glm::angle(newOrientation, m_Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		m_Orientation = newOrientation;
	}

	// Rotates the Orientation left and right
	m_Orientation = glm::rotate(m_Orientation, glm::radians(-rotY), m_Up);
}

