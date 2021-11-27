#include "Scene.h"

#include <GLFW/glfw3.h>
#include <GL/Camera.h>
#include "SceneLoader.h"

#include <memory>

namespace WE {

	Scene::Scene()
		: m_EntityManager(new EntityManager())
		, m_ComponentManager(new ComponentManager())
		, m_SystemManager(new SystemMamanger())
	{
		
	}

	void Scene::Update(const float dt)
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