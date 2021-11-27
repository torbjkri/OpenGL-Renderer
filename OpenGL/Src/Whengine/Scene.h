#pragma once

#include <vector>
#include <memory>

#include "ECS/EntityManager.h"
#include "ECS/ComponentManager.h"
#include "ECS/SystemManager.h"

#include <GLFW/glfw3.h>

#include "SceneLoader.h"

namespace WE {

class Scene {
private:
	std::unique_ptr<EntityManager> m_EntityManager;
	std::unique_ptr<ComponentManager> m_ComponentManager;
	std::unique_ptr<SystemMamanger> m_SystemManager;

public:

	void Update();

	//Maybe not needed
	void RenderScene();
	void RenderGui();
};
}