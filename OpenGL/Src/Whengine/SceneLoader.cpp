#include "SceneLoader.h"

#include <GL/Renderable/RenderableObject.h>
#include <GL/Renderable/Cube.h>
#include <GL/ResourceManager.h>

#include <nlohmann/json.hpp>
#include <string>
#include <Whengine/Scene.h>
#include <fstream>
#include <iostream>
#include <cstdlib>

using json = nlohmann::json;

namespace WE {
	Cube LoadCube(json& obj)
	{
		try {
			auto rm = ResourceManager::GetInstance();
			Texture diffuse = rm->LoadTexture(obj["textures"]["diffuse"]["filepath"],
				obj["textures"]["diffuse"]["name"], TextureType::DIFFUSE);
			Texture spec = rm->LoadTexture(obj["textures"]["specular"]["filepath"],
				obj["textures"]["specular"]["name"], TextureType::SPECULAR);
			Shader shader = rm->LoadShader("Resources/Shaders/Lighting/BasicShader.glsl", "texture-cube");

			return Cube(shader, diffuse, spec);
		}
		catch (json::exception& e) {
			std::cout << e.what() << std::endl;
			std::abort();
		}
	}

	void LoadScene(std::string filename)
	{
		std::ifstream ifs(filename);
		json j = json::parse(ifs);
		for (auto& [key,elem] : j.items()) {
			if (key == "cube") {
				for (auto& cubedata: elem)
				Cube cube = LoadCube(cubedata);
				
			}
		}
	}
}