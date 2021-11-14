#pragma once


namespace WE {

class Scene {
private:
	//-//-//-//-//-//-//-//-//
	// Renderable Objects;  //
	// Static solid Renderable     //
	// Lights               //
	// Camera               //
	//-//-//-//-//-//-//-//-//
public:

	void Update();

	// Is visitor correct?
	void Render(const Renderer& renderer);

	//Maybe not needed
	void RenderGui();
};
}