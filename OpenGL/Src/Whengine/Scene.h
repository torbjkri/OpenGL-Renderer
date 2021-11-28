#pragma once

#include <vector>
#include <memory>

#include <glm/mat4x4.hpp>


#include "ECS/Core/Entity.hpp"

class EntityManager;
class ComponentManager;
class RenderSystem;

namespace WE {

class Scene {
private:
	std::unique_ptr<EntityManager> m_EntityManager;
	std::unique_ptr<ComponentManager> m_ComponentManager;
	std::vector<std::unique_ptr<RenderSystem>> m_RenderSystems;

	glm::mat4 m_ProjectionView;

public:

	Scene();
	~Scene();

	//Maybe not needed
	void RenderScene();

	// Entity functions
	Entity CreateEntity();

	// Component functions
	template<typename T>
	T& GetComponent(Entity entity);

	template<typename T>
	void AddComponent(Entity entity, T component);

	// System functions
	void AddRenderSystem(std::unique_ptr<RenderSystem> system);

	glm::mat4 GetSceneProjectionView() const { return m_ProjectionView; }
};
} // namespace WE