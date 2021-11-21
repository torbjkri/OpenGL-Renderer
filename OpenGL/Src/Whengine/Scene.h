#pragma once

#include <vector>
#include <memory>

#include <GL/Renderable/RenderableObject.h>
#include <GL/Camera.h>
#include <GL/Renderable/Light.h>
#include <GL/Renderable/ObjectRenderer.h>
#include <GLFW/glfw3.h>

#include "SceneLoader.h"

namespace WE {

class Scene {
private:
	SceneData m_SceneData;
	std::shared_ptr<Camera> m_ViewCamera;
	ObjectRenderer m_Renderer;

public:
	Scene(GLFWwindow* window, std::shared_ptr<Camera> cam);
	void Update();

	//Maybe not needed
	void RenderScene();
	void RenderGui();
};
}