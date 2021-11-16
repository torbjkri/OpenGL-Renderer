#include "Whengine.h"

#include <memory>

namespace WE {

Whengine::Whengine()
	: m_Context(std::make_shared<GLContext>(new GLContext()))
	, m_InputHandler(std::make_shared<InputHandler>(new InputHandler(m_Context->GetWindow()))
{
	Scene(m_Context.GetWindow());
	/* Create Context/Window manager */

	/* Create Input manager/GUI rendere */

	/* Set up renderer */

	/* Load scene */
}

void Whengine::Run()
{
	/*Get/Handle inputs*/

	/*Update scene */

	/* Start frame */
	/* Render      */
	/* Render GUI  */
	/* End frame   */
}

}