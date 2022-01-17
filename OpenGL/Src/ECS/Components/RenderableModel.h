#pragma once

#include "GL/Core/Shader.h"
#include "GL/Model.h"

#include <memory>

struct RenderableModel
{
	std::shared_ptr<Model> model_;
	std::shared_ptr<Shader> shader_;

	void Render(const glm::mat4 projectioview, const glm::mat4 model)
	{
		model_->Render(shader_.get(), projectioview, model);
	}
};