#pragma once
#include <string>

#include <mutex>
#include <unordered_map>
#include <GL/Texture.h>
#include <GL/Shader.h>

class ResourceManager
{
private:
	ResourceManager() = default;
	static ResourceManager * s_Instance;
	static std::mutex s_Mutex;

	static std::unordered_map<std::string, Texture> s_Textures;
	static std::unordered_map<std::string, Shader> s_Shaders;

public:
	ResourceManager(ResourceManager& other) = delete;
	void operator=(const ResourceManager&) = delete;

	static ResourceManager* GetInstance();

	void LoadTexture(const std::string filePath, const std::string name);
	void LoadShader(const std::string filePath, const std::string name);
	
	Texture GetTexture(const std::string name);
	Shader GetShader(const std::string name);
};

