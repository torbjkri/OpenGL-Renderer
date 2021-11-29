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


			for (int i = 0; i < 100; i++) {
				Entity entity = m_Scene->CreateEntity();


				RenderableCube renderableCube{
					.color_ = glm::vec4(rander(), rander(), rander(), 1.0f),
					.cube_ = cube,
					.shader_ = shader
				};
				m_Scene->AddComponent(entity, renderableCube);

				Transform transform{
					.position_ = glm::vec3(rander()* 1.0f, -3.0f + 1.0f * rander(), rander()*3 ),
					.orientation_ = glm::vec3(00.0f * rander(), 00.0f * rander(), 00.0f * rander()),
					.scale_ = glm::vec3(rander())
				};
				m_Scene->AddComponent(entity, transform);

				Gravity g{ .force_ = glm::vec3(0.0f, -9.81f + 2.0f * rander(),0.0f) };
				m_Scene->AddComponent(entity, g);

				Velocity v;
				v.velocity_ = glm::vec3(5.0f * rander(), 20.0f + 0.05 * rander(), 5.0f * rander());
				m_Scene->AddComponent(entity, v);

			}
			
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