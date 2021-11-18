#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

//#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>


class Camera
{
private:
	// Stores the main vectors of the camera
	glm::vec3 m_Position;
	glm::vec3 m_Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

	// Stores the width and height of the window
	int m_Width;
	int m_Height;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float m_Speed = 0.1f;
	float m_Sensitivity = 100.0f;



public:
	// Camera constructor to set up initial values
	Camera(GLFWwindow *window);

	// Updates and exports the camera matrix to the Vertex Shader
	glm::mat4 GetProjectionView() const;
	glm::vec3 GetPosition() const;

	// Handles camera inputs
	void MoveForward();
	void MoveBackward();
	void MoveUp();
	void MoveDown();
	void StrafeLeft();
	void StrafeRight();
	void SetSpeed(const float speed);

	void MouseTurn(const int xPos, const int yPos);
};
