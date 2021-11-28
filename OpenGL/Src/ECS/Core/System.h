#pragma once

#include "Entity.hpp"
#include <set>
#include <memory>
#include "Whengine/Scene.h"

class System
{
protected:
	std::set<Entity> m_Entities;
	WE::Scene* m_Scene;
	Signature m_Signature;

public:
	// Constructor, connect system to scene
	System(std::shared_ptr<WE::Scene> scene) : m_Scene(scene.get()) {}

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
	virtual void Render() = 0;
};

class InteractionSystem : public System
{
	virtual void Update(const float dt) = 0;
};