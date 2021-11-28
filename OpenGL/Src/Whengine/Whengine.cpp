#include "Whengine.h"
#include <GL/Camera.h>
#include "SceneLoader.h"
#include "ECS/Components/RenderableCube.h"
#include "ECS/Components/Transform.h"

#include <memory>

namespace WE {

	Whengine::Whengine()
		: m_Context(std::make_shared<GLContext>())
	{
		auto cam = std::make_shared<Camera>(m_Context->GetWindow());
		//m_InputHandler = std::make_shared<InputHandler>(m_Context->GetWindow(), cam);
		m_Scene = std::make_unique<Scene>(cam);
		//Scene(m_Context->GetWindow(), cam);
		/* Create Context/Window manager */

		/* Create Input manager/GUI rendere */

		/* Set up renderer */

		/* Load scene */
		{
			std::unique_ptr<CubeRenderSystem> cubeRenderer;
			m_Scene->AddRenderSystem(std::move(cubeRenderer));
			Entity entity = m_Scene->CreateEntity();

			std::shared_ptr<CubeData> cube = std::make_shared<CubeData>(new CubeData());
			std::shared_ptr<Shader> shader = std::make_shared<Shader>(new Shader());
			std::unique_ptr<RenderableCube> renderableCube = std::make_unique<RenderableCube>(
				new RenderableCube{
					.color_ = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
					.cube_ = cube,
					.shader_ =  shader
				});
			m_Scene->AddComponent(entity, std::move(cube));

			std::unique_ptr<Transform> transform = std::make_unique<Transform>(
				new Transform{
					.position_ = glm::vec3(0.0f),
					.orientation_ = glm::vec3(0.0f),
					.scale_ = glm::vec3(0.2f)
				}
			);

			m_Scene->AddComponent(entity, std::move(transform));
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