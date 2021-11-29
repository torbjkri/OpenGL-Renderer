#pragma once

#include "Entity.hpp"
#include <set>
#include <memory>
#include "Component.h"

#include <iostream>

namespace WE { class Scene; }

class System
{
protected:
	std::set<Entity> m_Entities;
	WE::Scene *m_ParentScene;
	Signature m_Signature;

public:
	// Constructor, connect system to scene
	System(std::shared_ptr<WE::Scene> scene) : m_ParentScene(scene.get()) {}

	void EntitySignatureChanged(Entity entity, Signature signature)
	{
		const bool signatureMatch = (signature & m_Signature) == m_Signature;
		const bool isRegistered = m_Entities.find(entity) != m_Entities.end();


		if (signatureMatch && !isRegistered)
			m_Entities.insert(entity);
		else if (!signatureMatch && isRegistered)
			m_Entities.erase(entity);
		
		return;
	}

	void EntityDestroyed(Entity entity)
	{
		m_Entities.erase(entity);
	}
};

class RenderSystem : public System
{
public:
	RenderSystem(std::shared_ptr<WE::Scene> scene) : System(scene) {}
	virtual void Render() = 0;
};

class InteractionSystem : public System
{
public:
	InteractionSystem(std::shared_ptr<WE::Scene> scene) : System(scene) {}
	virtual void Update(const float dt) = 0;
};