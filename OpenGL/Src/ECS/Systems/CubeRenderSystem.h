#pragma once

#include "ECS/Core/System.h"
#include "Whengine/Scene.h"

#include "ECS/Components/RenderableCube.h"
#include "ECS/Components/Transform.h"

#include "GL/Core/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

class CubeRenderSystem : public RenderSystem
{
private:

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
	CubeRenderSystem(std::shared_ptr<WE::Scene> scene) : RenderSystem(scene) {}

	void Render() override
	{
		glm::mat4 modelView = m_ParentScene->GetSceneProjectionView();

		for (auto& entity : m_Entities) {
			auto& renderable = m_ParentScene->GetComponent<RenderableCube>(entity);
			auto& transform = m_ParentScene->GetComponent<Transform>(entity);

			renderable.shader_->Bind();
			renderable.cube_->Bind();
			renderable.shader_->SetUniform4fv("u_Color", 1, renderable.color_);

			glm::mat4 R = CreateModelMatrix(transform);
			R = modelView * R;

			renderable.shader_->SetUniformMatrix4fv("u_R", 1, R);

			renderable.Render();

		}
	}
};