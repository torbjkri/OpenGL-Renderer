#include "Whengine.h"
#include <GL/Camera.h>
#include "SceneLoader.h"
#include "Scene.h"

#include "ECS/Core/Entity.hpp"
#include "ECS/Core/EntityManager.h"
#include "ECS/Core/ComponentManager.h"
#include "ECS/Core/System.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/RenderableCube.h"
#include "ECS/Components/Gravity.h"
#include "ECS/Components/Velocity.h"

#include "ECS/Systems/CubeRenderSystem.h"
#include "ECS/Systems/PhysicsSystem.h"

#include <memory>
#include <cstdlib>
#include <ctime>

static float rander()
{
	return  2.0f * static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) - 1.0f;
}

namespace WE {

	Whengine::Whengine()
		: m_Context(std::make_shared<GLContext>())
	{
		//auto cam = std::make_shared<Camera>(m_Context->GetWindow());
		//m_InputHandler = std::make_shared<InputHandler>(m_Context->GetWindow(), cam);
		m_Scene = std::make_shared<Scene>();
		//Scene(m_Context->GetWindow(), cam);
		/* Create Context/Window manager */

		/* Create Input manager/GUI rendere */

		/* Set up renderer */

		/* Load scene */
		{
			std::shared_ptr<CubeData> cube = std::make_shared<CubeData>();
			std::shared_ptr<Shader> shader = std::make_shared<Shader>("Resources/Shaders/Basic/BasicColor.shader");

			std::unique_ptr<CubeRenderSystem> cubeRenderer = std::make_unique<CubeRenderSystem>(m_Scene);
			m_Scene->AddRenderSystem(std::move(cubeRenderer));

			std::unique_ptr<PhysicsSystem> physics = std::make_unique<PhysicsSystem>(m_Scene);
			m_Scene->AddInteractionSystem(std::move(physics));


			
			Entity entity1 = m_Scene->CreateEntity();


			RenderableCube renderableCube{
				.color_ = glm::vec4(rander(), rander(), rander(), 1.0f),
				.cube_ = cube,
				.shader_ = shader
			};
			m_Scene->AddComponent(entity1, renderableCube);

			Transform transform{
				.position_ = glm::vec3(-20.0f, 0.0f, 0.0f),
				.orientation_ = glm::vec3(0.0f),
				.scale_ = glm::vec3(1.0f)
			};
			m_Scene->AddComponent(entity1, transform);

			Gravity g{ .force_ = glm::vec3(0.0f) };
			m_Scene->AddComponent(entity1, g);

			Velocity v;
			v.velocity_ = glm::vec3(5.0f, 0.0f, 0.0f);
			m_Scene->AddComponent(entity1, v);

			// Entity 2
			Entity entity2 = m_Scene->CreateEntity();


			RenderableCube renderableCube2{
				.color_ = glm::vec4(rander(), rander(), rander(), 1.0f),
				.cube_ = cube,
				.shader_ = shader
			};
			m_Scene->AddComponent(entity2, renderableCube2);

			Transform transform2{
				.position_ = glm::vec3(20.0f, 0.0f, 0.0f),
				.orientation_ = glm::vec3(0.0f),
				.scale_ = glm::vec3(1.0f)
			};
			m_Scene->AddComponent(entity2, transform2);

			Gravity g2{ .force_ = glm::vec3(0.0f) };
			m_Scene->AddComponent(entity2, g2);

			Velocity v2;
			v2.velocity_ = glm::vec3(-5.0f, 0.0f, 0.0f);
			m_Scene->AddComponent(entity2, v2);
			
			
		}

	}

void Whengine::Run()
{
	/*Get/Handle inputs*/
	while (!m_Context->ShouldClose()) {
		m_Context->BeginFrame();
		//m_InputHandler->ProcessInput();
		m_Scene->Update(0.01f);
		m_Scene->RenderScene();
		m_Context->EndFrame();
	}

	/*Update scene */

	/* Start frame */
	/* Render      */
	/* Render GUI  */
	/* End frame   */
}

}