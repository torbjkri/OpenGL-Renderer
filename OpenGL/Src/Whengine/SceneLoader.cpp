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
	std::unique_ptr<Cube> LoadCube(json& obj)
	{
		try {
			auto rm = ResourceManager::GetInstance();
			Texture diffuse = rm->LoadTexture(obj["textures"]["diffuse"]["filepath"],
				obj["textures"]["diffuse"]["name"], TextureType::DIFFUSE);
			Texture spec = rm->LoadTexture(obj["textures"]["specular"]["filepath"],
				obj["textures"]["specular"]["name"], TextureType::SPECULAR);
			Shader shader = rm->LoadShader("Resources/Shaders/Lighting/BasicShader.glsl", "texture-cube");

			auto cube =  std::make_unique<Cube>(shader, diffuse, spec);

			if (obj.contains("position")) {
				std::vector<float> j_pos = obj["position"];
				cube->position_ = glm::vec3(j_pos[0], j_pos[1], j_pos[2]);
			}

			if (obj.contains("orientation")) {
				std::vector<float> j_ori = obj["orientation"];
				glm::vec3 orientation = glm::vec3(j_ori[0], j_ori[1], j_ori[2]);
				glm::mat4 R = glm::rotate(glm::mat4(1.0f), orientation.z, glm::vec3(0.0f, 0.0f, 1.0f));
				R = glm::rotate(R, orientation.y, glm::vec3(0.0f, 1.0f, 0.0f));
				R = glm::rotate(R, orientation.x, glm::vec3(1.0f, 0.0f, 0.0f));
				cube->orientation_mat_ = R;
			}

			return cube;

		}
		catch (json::exception& e) {
			std::cout << e.what() << std::endl;
			std::abort();
		}
	}

	std::unique_ptr<Light> LoadLight(json& obj)
	{
		try {
			auto rm = ResourceManager::GetInstance();

			Shader shader = rm->LoadShader("Resources/Shaders/Lighting/Light.glsl", "light");
			std::unique_ptr<PointLight> light = std::make_unique<PointLight>(shader);

			if (obj.contains("position")) {
				std::vector<float> j_pos = obj["position"];
				light->position_ = glm::vec3(j_pos[0], j_pos[1], j_pos[2]);
			}

			if (obj.contains("scale"))
				light->scale_ = obj["scale"];

			if (obj.contains("light-properties")) {
				std::vector<float> j_amb = obj["light-properties"]["ambient"];
				std::vector<float> j_dif = obj["light-properties"]["diffuse"];
				std::vector<float> j_spe = obj["light-properties"]["specular"];
				light->properties_.ambient_ = glm::vec3(j_amb[0], j_amb[1], j_amb[2]);
				light->properties_.diffuse_ = glm::vec3(j_dif[0], j_dif[1], j_dif[2]);
				light->properties_.specular_ = glm::vec3(j_spe[0], j_spe[1], j_spe[2]);
			}

			if (obj.contains("attenuation")) {
				light->attenuation_.constant_ = obj["attenuation"]["constant"];
				light->attenuation_.linear_ = obj["attenuation"]["linear"];
				light->attenuation_.quadratic_ = obj["attenuation"]["quadratic"];
			}

			return light;
		}
		catch (json::exception& e) {
			std::cout << e.what() << std::endl;
			std::abort();
		}
	}

	SceneData LoadScene(std::string filename)
	{
		std::ifstream ifs(filename);
		json j = json::parse(ifs);

		SceneData scene_data_;

		for (auto& [key, elem] : j.items()) {
			if (key == "cube") {
				for (auto& cubedata : elem)
					scene_data_.renderables_.push_back(LoadCube(cubedata));

			}
			if (key == "light") {
				for (auto& lightdata : elem) {
					scene_data_.lights_.push_back(LoadLight(lightdata));
				}
			}
		}

		return scene_data_;
	}
} // namespace WE