#pragma once

#include "ECS/Core/System.h"
#include "Whengine/Scene.h"

#include "ECS/Components/RenderableModel.h"
#include "ECS/Components/RenderableBall.h"
#include "ECS/Components/RenderableCube.h"
#include "ECS/Components/Transform.h"

#include "GL/Core/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include <iostream>

class CubeRenderSystem : public RenderSystem
{
public:
	CubeRenderSystem(std::shared_ptr<WE::Scene> scene)
		: RenderSystem(scene)
	{
		m_ParentScene->RegisterComponent<RenderableCube>();
		m_ParentScene->RegisterComponent<Transform>();

		m_Signature.set(m_ParentScene->GetComponentType<RenderableCube>());
		m_Signature.set(m_ParentScene->GetComponentType<Transform>());
	}

	void Render() override
	{
		glm::mat4 modelView = m_ParentScene->GetSceneProjectionView();

		for (auto& entity : m_Entities) {
			auto& renderable = m_ParentScene->GetComponent<RenderableCube>(entity);
			auto& transform = m_ParentScene->GetComponent<Transform>(entity);

			renderable.shader_->Bind();
			renderable.cube_->Bind();
			renderable.shader_->SetUniform4fv("u_Color", 1, renderable.color_);

			glm::mat4 R = transform.CreateModelMatrix();
			R = modelView * R ;

			renderable.shader_->SetUniformMatrix4fv("u_ProjectionViewModel", 1, R);

			renderable.Render();
			
			
		}
	}
};

class BallRenderSystem : public RenderSystem
{
public:
	BallRenderSystem(std::shared_ptr<WE::Scene> scene)
		: RenderSystem(scene)
	{
		m_ParentScene->RegisterComponent<RenderableBall>();
		m_ParentScene->RegisterComponent<Transform>();

		m_Signature.set(m_ParentScene->GetComponentType<RenderableBall>());
		m_Signature.set(m_ParentScene->GetComponentType<Transform>());
	}

	void Render() override
	{
		glm::mat4 modelView = m_ParentScene->GetSceneProjectionView();

		for (auto& entity : m_Entities) {
			auto& renderable = m_ParentScene->GetComponent<RenderableBall>(entity);
			auto& transform = m_ParentScene->GetComponent<Transform>(entity);

			renderable.shader_->Bind();
			renderable.cube_->Bind();
			renderable.shader_->SetUniform4fv("u_Color", 1, renderable.color_);

			glm::mat4 R = transform.CreateModelMatrix();
			R = modelView * R;

			renderable.shader_->SetUniformMatrix4fv("u_ProjectionViewModel", 1, R);

			renderable.Render();


		}
	}
};

class ModelRenderSystem : public RenderSystem
{
public:
	ModelRenderSystem(std::shared_ptr<WE::Scene> scene)
		: RenderSystem(scene)
	{
		m_ParentScene->RegisterComponent<RenderableModel>();
		m_ParentScene->RegisterComponent<Transform>();

		m_Signature.set(m_ParentScene->GetComponentType<RenderableModel>());
		m_Signature.set(m_ParentScene->GetComponentType<Transform>());
	}

	void Render() override
	{
		glm::mat4 modelView = m_ParentScene->GetSceneProjectionView();

		for (auto& entity : m_Entities) {
			auto& renderable = m_ParentScene->GetComponent<RenderableModel>(entity);
			auto& transform = m_ParentScene->GetComponent<Transform>(entity);
			
			renderable.Render(m_ParentScene->GetSceneProjectionView(), transform.CreateModelMatrix());
		}
	}
};