#pragma once

#include "Component.h"
#include "ComponentArray.h"
#include <unordered_map>
#include <memory>
#include <cassert>


class ComponentManager
{
private:

	// Map from char pointer to component type
	std::unordered_map<const char*, ComponentType> component_types_{};

	// Map form string pointer to component array
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> component_arrays_;

	// Component type to be assigned to the next registered component
	ComponentType next_component_type_;

	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		const char* type_name = typeid(T).name();
		assert(component_types_.find(type_name) != component_types_.end());

		return std::static_pointer_cast<ComponentArray<T>>(component_arrays_[type_name]);
	}

public:
	template<typename T>
	void RegisterComponent()
	{
		const char* type_name = typeid(T).name();
		assert(component_types_.find(type_name) == component_types_.end());

		component_types_.insert({ type_name, next_component_type_ });

		component_arrays_.insert({ type_name, std::make_shared<ComponentArray<T>>() });

		next_component_type_++;
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		const char* type_name = typeid(T).name();

		assert(component_types_.find(type_name) != component_types_.end());

		return component_types_[type_name];
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		GetComponentArray<T>()->InsertData(entity, component);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		return GetComponentArray<T>()->GetData(entity);
	}

	void EntityDestroyed(Entity entity)
	{
		// Notify each component that an entity was destroyed
		for (auto const& pair : component_arrays_) {
			auto const& component = pair.second;
			component->EntityDestroyed(entity);
		}
	}


};