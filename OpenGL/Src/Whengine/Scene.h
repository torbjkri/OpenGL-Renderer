#pragma once

#include <vector>
#include <memory>

#include <GL/Renderable/RenderableObject.h>
#include <GL/Camera.h>
#include <GL/Renderable/Light.h>
#include <GL/Renderable/ObjectRenderer.h>
#include <GLFW/glfw3.h>

namespace WE {

class Scene {
private:
	std::vector<std::unique_ptr<RenderableObject>> m_Objects;
	Camera m_ViewCamera;
	Light m_Light;
	ObjectRenderer m_Renderer;

public:
	Scene(GLFWwindow* window);
	void Update();

	//Maybe not needed
	void RenderScene();
	void RenderGui();
};
}