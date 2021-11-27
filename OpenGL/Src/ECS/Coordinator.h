#pragma once

#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

#include <memory>

class Coordinator {
private:
	std::unique_ptr<EntityManager> entity_manager_;
	std::unique_ptr<ComponentManager> component_manager_;
	std::unique_ptr<SystemMamanger> system_mamager_;

public:
	void Init()
	{
		entity_manager_ = std::make_unique<EntityManager>();
		component_manager_ = std::make_unique<ComponentManager>();
		system_mamager_ = std::make_unique<SystemMamanger>();
	}

	Entity CreateEntity()
	{
		return entity_manager_->create_entity();
	}

	void DestroyEntity(Entity entity)
	{
		entity_manager_->destroy_entity(entity);
		component_manager_->EntityDestroyed(entity);
		system_mamager_->EntityDestroyed(entity);
	}

	template<typename T>
	void RegisterComponent(T component)
	{
		component_manager_-><T>RegisterComponent();
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		component_manager_->AddComponent<T>entity, component);

		auto signature = entity_manager_->get_signature(entity);
		signature.set(component_manager_->GetComponentType<T>(), true);
		entity_manager_->set_signature(entity, signature);
		system_mamager_->EntitySignatureChanged(entity, signature);
	}

		template<typename T>
		void RemoveComponent(Entity entity, T component)
		{
			component_manager_->RemoveComponent<T>(entity);
			auto signature = entity_manager_->get_signature(entity);
			signature.set(component_manager_->GetComponentType<T>(), false);
			entity_manager_->set_signature(entity, signature);
			system_mamager_->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		T& GetComponent(Entity entity)
		{
			return component_manager_->GetComponent<T>(entity);
		}

		template<typename T>
		ComponentType GetComponentType()
		{
			return component_manager_->GetComponentType<T>();	
		}

		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			return system_mamager_->RegisterSystem<T>();
		}

		template<typename T>
		void SetSystemSignature(Signature signature)
		{
			system_mamager_->SetSignature(signature);
		}
};