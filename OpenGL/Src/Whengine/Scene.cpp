#include "Scene.h"

#include <GLFW/glfw3.h>
#include <GL/Camera.h>
#include "SceneLoader.h"

#include <memory>

namespace WE {

	Scene::Scene(std::shared_ptr<Camera> cam)
		: m_ViewCamera(cam)
	{
		m_SceneData = LoadScene("Resources/Scenes/boxlight.json");
	}

	void Scene::Update()
	{

	}

	void Scene::RenderScene()
	{
		for (auto& obj : m_SceneData.renderables_)
		{
			m_Renderer.Draw(obj, m_SceneData.lights_[0], m_ViewCamera->GetProjectionView(), m_ViewCamera->GetPosition());
		}

		for (auto& light : m_SceneData.lights_)
			m_Renderer.Draw(light, m_ViewCamera->GetProjectionView());
	}

	void Scene::RenderGui()
	{

	}







} // namespace WE