#pragma once

#include <nlohmann/json.hpp>
#include <GL/Renderable/RenderableObject.h>
#include <GL/Renderable/Light.h>
#include <GL/Core/Texture.h>
#include <GL/Core/Shader.h>

#include <string>
#include <memory>


namespace WE {

	struct SceneData {
		std::vector<std::unique_ptr<RenderableObject>> renderables_;
		std::vector<std::unique_ptr<Light>> lights_;
	};

	SceneData LoadScene(std::string filename);

} // namespace WE