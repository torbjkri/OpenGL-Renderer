#pragma once

#include <nlohmann/json.hpp>
#include <Whengine/Scene.h>

#include <string>

namespace WE {

	Scene LoadScene(std::string filename);

} // namespace WE