#pragma once

#include <mutex>
#include <unordered_map>
#include <GL/Texture.h>
#include <GL/Shader.h>

class ResourceManager
{
private:
	ResourceManager();
	static ResourceManager * s_Instance;
	static std::mutex s_Mutex;

	static std::unordered_map<std::string, Texture> s_Textures;
	static std::unordered_map<std::string, Shader> s_Shader;

public:
	ResourceManager(ResourceManager& other) = delete;
	void operator=(const ResourceManager&) = delete;

	static ResourceManager* GetInstance();
};

