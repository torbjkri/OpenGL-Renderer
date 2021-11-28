#include "Scene.h"

#include "SceneLoader.h"

#include <memory>
#include <glm/mat4x4.hpp>

#include "ECS/Core/ComponentManager.h"
#include "ECS/Core/EntityManager.h"
#include "ECS/Core/System.h"

namespace WE {

	Scene::Scene()
		: m_EntityManager(new EntityManager())
		, m_ComponentManager(new ComponentManager())
		, m_ProjectionView(1.0f)
	{
		
	}

	Scene::~Scene()
	{
	}

	void Scene::RenderScene()
	{
		for (auto& system : m_RenderSystems)
			system->Render();
	}

	Entity Scene::CreateEntity()
	{
		return m_EntityManager->CreateEntity();
	}


	// Component functions
	template<typename T>
	T& Scene::GetComponent(Entity entity)
	{
		return m_ComponentManager->GetComponent<T>(entity);
	}

	template<typename T>
	void Scene::AddComponent(Entity entity, T component)
	{
		m_ComponentManager->AddComponent<T>(entity, component);
		Signature signature = m_EntityManager->GetSignature();
		signature.set(m_ComponentManager->GetComponentType<T>());
		m_EntityManager->SetSignature(entity, signature);
		
		for (auto& system : m_RenderSystems)
			system->EntitySignatureChanged(entity, signature);
	}


	// System functions
	void Scene::AddRenderSystem(std::unique_ptr<RenderSystem> system)
	{
		m_RenderSystems.push_back(std::move(system));
	}




} // namespace WE