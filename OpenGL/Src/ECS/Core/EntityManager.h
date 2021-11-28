#pragma once

#include <queue>
#include <array>
#include <cassert>

#include "Entity.hpp"
#include "Component.h"

class EntityManager
{
private:
	std::queue<Entity> m_AvailableEntities;
	std::uint16_t m_LivingEntityCount{};
	std::array<Signature, MAX_ENTITIES> m_Signatures;

public:
	EntityManager()
	{
		for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
			m_AvailableEntities.push(entity);
		}
	}

	Entity CreateEntity()
	{
		assert(m_LivingEntityCount < MAX_ENTITIES && "Too many living entities");

		Entity id = m_AvailableEntities.front();
		m_AvailableEntities.pop();
		m_LivingEntityCount++;
		return id;
	}

	Entity DestroyEntity(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range");

		m_Signatures[entity].reset();
		m_AvailableEntities.push(entity);
		m_LivingEntityCount--;
	}

	void SetSignature(Entity entity, Signature signature)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range");

		m_Signatures[entity] = signature;
	}

	Signature GetSignature(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range");

		return m_Signatures[entity];
	}
};
