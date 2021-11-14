#pragma once


namespace WE {

class Application {
private:
	/*Context/Window manager
		- Create OpenGL context and window
		- Winow interaction callbacks (minimize, close, resize)
	*/
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

	/*Renderer/ Render Manager
		- Accept scene objects and global states (e.g. lights) and render them.
		- Should it do pre render, and post-render handling?
	*/
	

public:
	 
	void Run();

};

}