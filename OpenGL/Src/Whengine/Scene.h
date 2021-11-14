#pragma once

#include <vector>
#include <memory>

#include <GL/Renderable/RenderableObject.h>

namespace WE {

class Scene {
private:
	std::vector<std::unique_ptr<RenderableObject>>
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