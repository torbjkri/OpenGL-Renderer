#pragma once

#include "ECS/Core/System.h"
#include "Whengine/Scene.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/Gravity.h"
#include "ECS/Components/Velocity.h"

namespace WE { class Scene; }

class PhysicsSystem : public InteractionSystem
{
public:
	PhysicsSystem(std::shared_ptr<WE::Scene> scene)
		: InteractionSystem(scene)
	{
		m_ParentScene->RegisterComponent<Transform>();
		m_ParentScene->RegisterComponent<Gravity>();
		m_ParentScene->RegisterComponent<Velocity>();

		m_Signature.set(m_ParentScene->GetComponentType<Gravity>());
		m_Signature.set(m_ParentScene->GetComponentType<Transform>());
		m_Signature.set(m_ParentScene->GetComponentType<Velocity>());

	}

	void Update(const float dt) override
	{
		for (auto& entity : m_Entities) {
			auto& gravity = m_ParentScene->GetComponent<Gravity>(entity);
			auto& transform = m_ParentScene->GetComponent<Transform>(entity);
			auto& velocity = m_ParentScene->GetComponent<Velocity>(entity);

			velocity.velocity_ += gravity.force_ * dt;
			transform.position_ += velocity.velocity_ * dt;
		}
	}
};