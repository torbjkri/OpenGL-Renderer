#pragma once

#include "System.h"
#include "Whengine/Scene.h"

class RenderSystem : public System
{
private:
	// The scene to which the system belongs
	WE::Scene* m_ParentScene;

public:
	void Render() override
	{
		for (auto& entity : entities_) {
			auto& renderable = m_ParentScene->GetComponent<RenderableCube>(entity);
			renderable->cube_->Bind();
		}
	}
};