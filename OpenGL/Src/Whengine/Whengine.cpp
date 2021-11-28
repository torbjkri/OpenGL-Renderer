#include "Whengine.h"
#include <GL/Camera.h>
#include "SceneLoader.h"
#include "ECS/Components/RenderableCube.h"
#include "ECS/Components/Transform.h"
#include "Scene.h"
#include "ECS/Core/System.h"
#include "ECS/Systems/CubeRenderSystem.h"

#include <memory>

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
			std::unique_ptr<CubeRenderSystem> cubeRenderer = std::make_unique<CubeRenderSystem>(m_Scene);
			m_Scene->AddRenderSystem(std::move(cubeRenderer));
			Entity entity = m_Scene->CreateEntity();

			std::shared_ptr<CubeData> cube = std::make_shared<CubeData>();
			std::shared_ptr<Shader> shader = std::make_shared<Shader>();
			RenderableCube renderableCube{
				.color_ = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
				.cube_ = cube,
				.shader_ = shader
			};
			m_Scene->AddComponent(entity, cube);

			Transform transform{
				.position_ = glm::vec3(0.0f),
				.orientation_ = glm::vec3(0.0f),
				.scale_ = glm::vec3(0.2f)
			};

			m_Scene->AddComponent(entity, transform);
		}

	}

void Whengine::Run()
{
	/*Get/Handle inputs*/
	while (!m_Context->ShouldClose()) {
		m_Context->BeginFrame();
		//m_InputHandler->ProcessInput();
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