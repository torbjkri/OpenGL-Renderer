#pragma once

#include "GL/Core/Shader.h"
#include "GL/Model.h"

#include <memory>

struct RenderableModel
{
	std::shared_ptr<Model> model_;
	std::shared_ptr<Shader> shader_;

	void Render()
	{
		model_->Render(shader_.get());
	}
};