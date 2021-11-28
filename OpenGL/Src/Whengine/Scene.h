#pragma once

#include <vector>
#include <memory>

#include "ECS/Core/EntityManager.h"
#include "ECS/Core/ComponentManager.h"
#include "ECS/Core/System.h"
#include "ECS/Systems/CubeRenderSystem.h"

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

#include "SceneLoader.h"

namespace WE {

class Scene {
private:
	std::unique_ptr<EntityManager> m_EntityManager;
	std::unique_ptr<ComponentManager> m_ComponentManager;
	std::vector<std::unique_ptr<RenderSystem>> m_RenderSystems;

	glm::mat4 m_ProjectionView;

public:

	//Maybe not needed
	void RenderScene();

	// Entity functions
	Entity CreateEntity() {return m_EntityManager->CreateEntity() }

	// Component functions
	template<typename T>
	T& GetComponent(Entity entity);

	// System functions
	void AddRenderSystem(std::unique_ptr<RenderSystem> system);

	glm::mat4 GetSceneProjectionView() const { return m_ProjectionView; }
};
}