#include "SceneLoader.h"

#include "nlohmann/json.hpp"
#include <string>
#include <Whengine/Scene.h>
#include <fstream>

namespace WE {
	Scene LoadScene(std::string filename)
	{
		std::ifstream ifs(filename);
		json obj = json::parse(ifs);
		for (auto& elem : obj) {
			std::count << elem["type"] << std::endl;
		}
	}
}