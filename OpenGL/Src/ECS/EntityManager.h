#pragma once

#include <queue>
#include <array>
#include <cassert>

#include "Entity.hpp"
#include "Component.h"

class EntityManager
{
private:
	std::queue<Entity> available_entities_;
	std::uint16_t living_entity_count_{};
	std::array<Signature, MAX_ENTITIES> signatures_;

public:
	EntityManager()
	{
		for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
			available_entities_.push(entity);
		}
	}

	Entity create_entity()
	{
		assert(living_entity_count_ < MAX_ENTITIES && "Too many living entities");

		Entity id = available_entities_.front();
		available_entities_.pop();
		living_entity_count_++;
		return id;
	}

	Entity destroy_entity(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range");

		signatures_[entity].reset();
		available_entities_.push(entity);
		living_entity_count_--;
	}

	void set_signature(Entity entity, Signature signature)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range");

		signatures_[entity] = signature;
	}

	Signature get_signature(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range");

		return signatures_[entity];
	}
};
