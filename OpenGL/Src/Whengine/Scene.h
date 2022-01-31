#pragma once

#include <vector>
#include <memory>

#include <glm/mat4x4.hpp>


#include "ECS/Core/Entity.hpp"
#include "ECS/Core/EntityManager.h"
#include "ECS/Core/ComponentManager.h"
#include "ECS/Core/System.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/RenderableCube.h"
#include "ECS/Components/Gravity.h"
#include "ECS/Components/Velocity.h"

#include "Resources/ResourceManager.h"

namespace WE {

class Scene {
private:
	std::unique_ptr<ResourceManager> m_ResourceManager;

	std::unique_ptr<EntityManager> m_EntityManager;
	std::unique_ptr<ComponentManager> m_ComponentManager;
	std::vector<std::unique_ptr<RenderSystem>> m_RenderSystems;
	std::vector<std::unique_ptr<InteractionSystem>> m_InteractionSystems;

	glm::mat4 m_ProjectionView;

public:

	Scene();
	~Scene();

	//Maybe not needed
	void RenderScene();
	void Update(const float dt);

	// Resource manager
	ResourceManager* GetResourceManager()
	{
		return m_ResourceManager.get();
	}

	// Entity functions
	Entity CreateEntity();

	// Component functions
	template<typename T>
	T& GetComponent(Entity entity)
	{
		return m_ComponentManager->GetComponent<T>(entity);
	}

	template<typename T>
	void RegisterComponent()
	{
		m_ComponentManager->RegisterComponent<T>();
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		return m_ComponentManager->GetComponentType<T>();
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		m_ComponentManager->AddComponent<T>(entity, component);
		Signature signature = m_EntityManager->GetSignature(entity);
		signature.set(m_ComponentManager->GetComponentType<T>());
		m_EntityManager->SetSignature(entity, signature);

		for (auto& system : m_RenderSystems)
			system->EntitySignatureChanged(entity, signature);

		for (auto& system : m_InteractionSystems)
			system->EntitySignatureChanged(entity, signature);
	}

	// System functions
	void AddRenderSystem(std::unique_ptr<RenderSystem> system);
	void AddInteractionSystem(std::unique_ptr<InteractionSystem> system);

	glm::mat4 GetSceneProjectionView() const { return m_ProjectionView; }
};
} // namespace WE