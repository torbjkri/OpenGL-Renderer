#pragma once

#include <array>
#include <unordered_map>
#include <cassert>

#include "Entity.hpp"

class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
private:

	// Packed component array
	std::array<T, MAX_ENTITIES> component_array_;

	// Map from entity ID to array index
	std::unordered_map<Entity, size_t> entity_to_index_map_;

	// Map from array index to specific entity
	std::unordered_map<size_t, Entity> index_to_entity_map_;

	size_t size_;

public:
	void InsertData(Entity entity, T component)
	{
		assert(entity_to_index_map_.find(entity) == entity_to_index_map_.end());

		size_t idx = size_;
		size_++;
		index_to_entity_map_[idx] = entity;
		entity_to_index_map_[entity] = idx;
		component_array_[idx] = component;
	}

	void RemoveData(Entity entity)
	{
		assert(entity_to_index_map_.find(entity) != entity_to_index_map_.end());

		size_t last_idx = size_ - 1;
		size_t idx = entity_to_index_map_[entity];
		component_array_[idx] = component_array_[last_idx];

		Entity last_entity = index_to_entity_map_[last_idx];
		entity_to_index_map_[last_entity] = idx;
		
		index_to_entity_map_[idx] = last_entity;
		
		entity_to_index_map_.erase(entity);
		index_to_entity_map_.rehash(last_idx);

		size_--;
	}

	T& GetData(Entity entity)
	{
		assert(entity_to_index_map_[entity] != entity_to_index_map_.end());

		// Returns reference to that entity's component
		return component_array_[entity_to_index_map_[entity]];
	}

	void EntityDestroyed(Entity entity) override
	{
		if (entity_to_index_map_[entity] != entity_to_index_map_.end())
			RemoveData(entity);
	}
};

