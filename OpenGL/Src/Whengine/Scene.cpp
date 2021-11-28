#include "Scene.h"

#include <GLFW/glfw3.h>
#include <GL/Camera.h>
#include "SceneLoader.h"

#include <memory>
#include <glm/mat4x4.hpp>

namespace WE {

	Scene::Scene()
		: m_EntityManager(new EntityManager())
		, m_ComponentManager(new ComponentManager())
	{
		
	}

	void Scene::RenderScene()
	{
		for (auto& system : m_RenderSystems)
			system->Render();
	}


	// Component functions
	template<typename T>
	T& Scene::GetComponent(Entity entity)
	{
		return m_ComponentManager->GetComponent<T>(entity);
	}


	// System functions
	void Scene::AddRenderSystem(std::unique_ptr<RenderSystem> system)
	{
		m_RenderSystems.push_back(std::move(system));
	}




} // namespace WE