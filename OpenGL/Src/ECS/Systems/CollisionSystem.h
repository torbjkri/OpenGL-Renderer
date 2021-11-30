#pragma once

#include "ECS/Core/System.h"
#include "Whengine/Scene.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/Collidable.h"



namespace WE { class Scene; }

class CollisionSystem : public InteractionSystem
{
public:
	CollisionSystem(std::shared_ptr<WE::Scene> scene)
		: InteractionSystem(scene)
	{
		m_ParentScene->RegisterComponent<Transform>();
		m_ParentScene->RegisterComponent<Collidable>();

		m_Signature.set(m_ParentScene->GetComponentType<Transform>());
		m_Signature.set(m_ParentScene->GetComponentType<Collidable>());

	}

	void Update(const float dt) override
	{
		for (auto& entity_1 : m_Entities) {
			auto& transform_1 = m_ParentScene->GetComponent<Transform>(entity_1);
			auto& collision_1 = m_ParentScene->GetComponent<Collidable>(entity_1);
			auto& velocity_1 = m_ParentScene->GetComponent<Velocity>(entity_1);

			for (auto& entity_2 : m_Entities) {
				if (entity_1 == entity_2)
					continue;
				
				auto& transform_2 = m_ParentScene->GetComponent<Transform>(entity_2);
				auto& collision_2 = m_ParentScene->GetComponent<Collidable>(entity_2);
				auto& velocity_2 = m_ParentScene->GetComponent<Velocity>(entity_2);

				if (Intersects(collision_1.shape_.get(), transform_1, collision_2.shape_.get(), transform_2)) {
					velocity_1.velocity_ = glm::vec3(0.0f);
					velocity_2.velocity_ = glm::vec3(0.0f);
				}

			}
		}
	}

private:
	bool Intersects(const CollisionBall* ball_1, const Transform& pos_1, const CollisionBall* ball_2, const Transform& pos_2)
	{
		const float r = glm::length(pos_1.position_ - pos_2.position_);
		return r < ball_1->radius_ + ball_2->radius_;
	}
};
