#include "Whengine.h"
#include <GL/Camera.h>
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
#include "ECS/Systems/CollisionSystem.h"

#include "Resources/ResourceManager.h"
#include "Resources/Model.h"


#include "Utilities/Timer.h"

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
			std::shared_ptr<Model> model = std::make_shared<Model>("C:/Users/torbj/Documents/Blender/GLModels/blank-ball/blank-ball.obj");
			//std::shared_ptr<Model> model = std::make_shared<Model>("Resources/Models/backpack/backpack.obj");

			std::shared_ptr<Shader> shader = std::make_shared<Shader>("Resources/Shaders/Basic/BasicColor.shader");

			auto modelRenderer = std::make_unique<ModelRenderSystem>(m_Scene);
			m_Scene->AddRenderSystem(std::move(modelRenderer));

			std::unique_ptr<PhysicsSystem> physics = std::make_unique<PhysicsSystem>(m_Scene);
			m_Scene->AddInteractionSystem(std::move(physics));

			//std::unique_ptr<CollisionSystem> collisys = std::make_unique<CollisionSystem>(m_Scene);
			//m_Scene->AddInteractionSystem(std::move(collisys));


			for (int i = 0; i < 1; i++) {

				Entity entity1 = m_Scene->CreateEntity();


				RenderableModel renderableModel{
					.model_ = model,
					.shader_ = shader
				};
				m_Scene->AddComponent(entity1, renderableModel);


				TransformState init_state{
					.position_ = glm::vec3(0,0,0),
					//.position_ = glm::vec3(0.0f, 0.0f, 18.0f),
					.orientation_ = glm::vec3(0.0f),
					.scale_ = glm::vec3(1.0f)
				};

				Transform t{ init_state, init_state };

				m_Scene->AddComponent(entity1, t);

				Gravity g{.force_ = glm::vec3(0.0f)};
				m_Scene->AddComponent(entity1, g);

				Velocity v;
				v.linear_ = glm::vec3(0.0f, 0.0f, 0.0f);
				v.angular_ = glm::vec3(0.0f, 20.0f, 0.0f);
				//v.velocity_ = glm::vec3(0.0f, 0.0f, 0.0f);
				m_Scene->AddComponent(entity1, v);

				//Collidable b;
				//CollisionBox box;
				//box.size_ = t.curr_state_.scale_;
				//b.shape_ = std::move(box);
				//m_Scene->AddComponent(entity1, b);

			}

			// Floor
			//Entity floor = m_Scene->CreateEntity();
			//
			//
			//RenderableCube floorCube{
			//	.color_ = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
			//	.cube_ = cube,
			//	.shader_ = shader
			//};
			//m_Scene->AddComponent(floor, floorCube);
			//
			//
			//
			//TransformState fstate{
			//	.position_ = glm::vec3(0.0f, -8.0f, 0.0f),
			//	.orientation_ = glm::vec3(0.0f),
			//	.scale_ = glm::vec3(30.0f, 0.1f, 30.0f)
			//};
			//
			//Transform tf{ fstate, fstate };
			//
			//m_Scene->AddComponent(floor, tf);
			//
			//Gravity rg{ .force_ = glm::vec3(0.0f) };
			//m_Scene->AddComponent(floor, rg);
			//
			//Velocity rv;
			//rv.velocity_ = glm::vec3(0.0f, 0.0f, 0.0f);
			//m_Scene->AddComponent(floor, rv);
			//
			//Collidable fb;
			//CollisionBox fbox;
			//fbox.size_ = fstate.scale_;
			//fb.shape_ = std::move(fbox);
			//m_Scene->AddComponent(floor, fb);
		}

	}

void Whengine::Run()
{
	/*Get/Handle inputs*/
	Timer timer(1000);
	while (!m_Context->ShouldClose()) {
		m_Context->BeginFrame();
		//m_InputHandler->ProcessInput();
		m_Scene->Update(timer.GetDeltaTime());
		m_Scene->RenderScene();
		m_Context->EndFrame();

		timer.Tick();
	}

	/*Update scene */

	/* Start frame */
	/* Render      */
	/* Render GUI  */
	/* End frame   */
}

}