#pragma once

#include "ECS/Core/System.h"
#include "Whengine/Scene.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/Collidable.h"

#include <variant>
#include <functional>


namespace WE { class Scene; }

struct CollisionVisitor {
	bool operator()(CollisionBall& ball1, CollisionBall& ball2, TransformState& t1, TransformState& t2)
	{
		const float r = glm::length(t1.position_ - t2.position_);
		return r < ball1.radius_ + ball2.radius_;
	}
	bool operator()(CollisionBall& ball1, CollisionBox& ball2, TransformState& t1, TransformState& t2)
	{
		return false;
	}
	bool operator()(CollisionBox& ball1, CollisionBall& ball2, TransformState& t1, TransformState& t2)
	{
		return false;
	}
	bool operator()(CollisionBox& ball1, CollisionBox& ball2, TransformState& t1, TransformState& t2)
	{
		// Simple AABB
		if (glm::length(t1.position_.x - t2.position_.x) < ball1.size_.x + ball2.size_.x) {
			if (glm::length(t1.position_.y - t2.position_.y) < ball1.size_.y + ball2.size_.y) {
				if (glm::length(t1.position_.z - t2.position_.z) < ball1.size_.z + ball2.size_.z) {
					return true;
				}
			}
		}


	return false;
	}
};



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


		for (auto entity_1 = m_Entities.begin(); entity_1 != m_Entities.end(); entity_1++) {
			for (auto entity_2 = std::next(entity_1, 1); entity_2 != m_Entities.end(); entity_2++) {

				auto& transform_1 = m_ParentScene->GetComponent<Transform>(*entity_1);
				auto& collision_1 = m_ParentScene->GetComponent<Collidable>(*entity_1);
				auto& velocity_1 = m_ParentScene->GetComponent<Velocity>(*entity_1);

				auto& transform_2 = m_ParentScene->GetComponent<Transform>(*entity_2);
				auto& collision_2 = m_ParentScene->GetComponent<Collidable>(*entity_2);
				auto& velocity_2 = m_ParentScene->GetComponent<Velocity>(*entity_2);

				auto f = std::bind(CollisionVisitor(), std::placeholders::_1, std::placeholders::_2, transform_1.curr_state_, transform_2.curr_state_);

				if (std::visit(f , collision_1.shape_, collision_2.shape_)) {
					transform_1.curr_state_ = transform_1.prev_state_;
					transform_2.curr_state_ = transform_2.prev_state_;
					velocity_1.velocity_ = -velocity_1.velocity_;
					velocity_2.velocity_ = -velocity_2.velocity_;
				}


			}
		}
	}

private:
	
};
