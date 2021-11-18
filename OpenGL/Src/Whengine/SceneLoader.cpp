#include "SceneLoader.h"

#include <nlohmann/json.hpp>
#include <string>
#include <Whengine/Scene.h>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

namespace WE {
	void LoadScene(std::string filename)
	{
		std::ifstream ifs(filename);
		json obj = json::parse(ifs);
		//for (auto& elem : obj) {
		std::cout << "\n" << obj << std::endl;
		//}
	}
}