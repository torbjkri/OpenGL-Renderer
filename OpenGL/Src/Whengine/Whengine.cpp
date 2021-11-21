#include "Whengine.h"
#include <GL/Camera.h>
#include "SceneLoader.h"

#include <memory>

namespace WE {

Whengine::Whengine()
	: m_Context(std::make_shared<GLContext>())
{
	auto cam = std::make_shared<Camera>(m_Context->GetWindow());
	m_InputHandler = std::make_shared<InputHandler>(m_Context->GetWindow(), cam);
	m_Scene = std::make_unique<Scene>(cam);
	//Scene(m_Context->GetWindow(), cam);
	/* Create Context/Window manager */

	/* Create Input manager/GUI rendere */

	/* Set up renderer */

	/* Load scene */
}

void Whengine::Run()
{
	/*Get/Handle inputs*/
	while (!m_Context->ShouldClose()) {
		m_Context->BeginFrame();
		m_InputHandler->ProcessInput();
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