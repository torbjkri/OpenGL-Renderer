#pragma once

#include "ECS/Core/System.h"
#include "Whengine/Scene.h"

#include "ECS/Components/RenderableCube.h"
#include "ECS/Components/Transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>>

class CubeRenderSystem : public RenderSystem
{
private:
	// The scene to which the system belongs
	WE::Scene* m_ParentScene;

	glm::mat4 CreateModelMatrix(Transform& transform)
	{
		glm::mat4 R(1.0f);
		R = glm::translate(R, transform.position_);
		R = glm::rotate(R, glm::radians(transform.orientation_.x), glm::vec3(1.0f, 0.0f, 0.0f));
		R = glm::rotate(R, glm::radians(transform.orientation_.y), glm::vec3(0.0f, 1.0f, 0.0f));
		R = glm::rotate(R, glm::radians(transform.orientation_.z), glm::vec3(0.0f, 0.0f, 1.0f));
		R = glm::scale(R, transform.scale_);

		return R;

	}

public:
	void Render() override
	{
		glm::mat4 modelView = m_ParentScene->GetSceneProjectionView();

		for (auto& entity : m_Entities) {
			auto& renderable = m_ParentScene->GetComponent<RenderableCube>(entity);
			auto& transform = m_ParentScene->GetComponent<Transform>(entity);

			renderable->shader_->Bind();
			renderable->cube_->Bind();
			renderable->shader_->SetVec4f("u_Color", renderable->color_);

			glm::mat4 R = CreateModelMatrix(transform);
			R = modelView * R;

			renderable->shader_->SetMatrix4fv("u_R", 1, R);

			renderable->cube_->Render();

		}
	}
};