#pragma once

#include <unordered_map>
#include <memory>
#include "System.h"
#include "Component.h"

class SystemMamanger
{
private:

	// Map from string name signature
	std::unordered_map<const char*, Signature> signatues_;

	// Map from string name to system pointer
	std::unordered_map<const char*, std::shared_ptr<System>> systems_;

public:
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		const char* type_name = typeid(T).name();

		assert(systems_.find(type_name) == systems_.end());

		auto system - std::make_shared<T>();
		systems_.insert({ type_name, system });
		return system;
	}

	template<typename T>
	void SetSignature(Signature signature)
	{
		const char* type_name = typeid(T).name();

		assert(systems_.find(type_name) != systems_.end());

		signatues_.insert({ type_name, signature });
	}

	void EntityDestroyed(Entity entity)
	{
		for (auto& const system : systems_)
		{
			system.second->entities_.erase(entity);
		}
	}

	void EntitySignatureChanged(Entity entity, Signature signature)
	{
		// Notify all systems that an entities signature changed
		for (auto const& pair : systems_)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& system_signature = signatues_[type];

			if ((signature & system_signature) == system_signature)
			{
				system->entities_.insert(entity);
			}
			else
			{
				system->entities_.erase(entity);
			}

		}
	}
};