#include "Scene.h"

#include "SceneLoader.h"

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ECS/Core/ComponentManager.h"
#include "ECS/Core/EntityManager.h"
#include "ECS/Core/System.h"

namespace WE {

	Scene::Scene()
		: m_EntityManager(new EntityManager())
		, m_ComponentManager(new ComponentManager())
		, m_ProjectionView(1.0f)
	{
		glm::vec3 position = glm::vec3( 0.0f, 0.0f, 20.0f );
		glm::vec3 orientation = glm::vec3( 0.0f, 0.0f, -1.0f );
		glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f );

		glm::mat4 view = glm::lookAt(position, position + orientation, up);
		glm::mat4 projection = glm::perspective(glm::radians(80.0f), 16.0f/9.0f, 0.1f, 100.0f);
		m_ProjectionView = projection * view;
		
	}

	Scene::~Scene()
	{
	}

	void Scene::RenderScene()
	{
		for (auto& system : m_RenderSystems)
			system->Render();
	}

	void Scene::Update(const float dt)
	{
		for (auto& system : m_InteractionSystems)
			system->Update(dt);
	}

	Entity Scene::CreateEntity()
	{
		return m_EntityManager->CreateEntity();
	}

	// System functions
	void Scene::AddRenderSystem(std::unique_ptr<RenderSystem> system)
	{
		m_RenderSystems.push_back(std::move(system));
	}

	void Scene::AddInteractionSystem(std::unique_ptr<InteractionSystem> system)
	{
		m_InteractionSystems.push_back(std::move(system));
	}




} // namespace WE