#pragma once

#include <GL/Core/GLContext.h>
#include "Scene.h"

namespace WE {

class Whengine {
private:
	/*Context/Window manager
		- Create OpenGL context and window
		- Winow interaction callbacks (minimize, close, resize)
	*/
	GLContext m_Context;


	/*IO Manger ??
		- Should it be mixed with ImGUI?
		- How should it communicate to other parts ?
			- Shared ptr?
			- Send as input
			- Give callback to
	*/

	/*Scene Manager
		- Maintain objects and their relationships
	*/
	Scene m_Scene;

	/*Renderer/ Render Manager
		- Accept scene objects and global states (e.g. lights) and render them.
		- Should it do pre render, and post-render handling?
	*/
	

public:
	 
	Whengine();
	void Run();

};

}