#include "ResourceManager.h"
#include <mutex>
#include <string>
#include <unordered_map>
#include <GL/Core/Texture.h>
#include <GL/Core/Shader.h>

#include <format>
#include <iostream>


ResourceManager* ResourceManager::s_Instance{ nullptr };
std::mutex ResourceManager::s_Mutex;

std::unordered_map<std::string, Texture> ResourceManager::s_Textures;
std::unordered_map<std::string, Shader> ResourceManager::s_Shaders;

ResourceManager* ResourceManager::GetInstance()
{
	std::lock_guard<std::mutex> lock(s_Mutex);
	if (s_Instance == nullptr)
		s_Instance = new ResourceManager();

	return s_Instance;
}

Texture ResourceManager::LoadTexture(const std::string filePath, const std::string name, TextureType type)
{
	if (s_Textures.find(name) == s_Textures.end())
		s_Textures[name] = Texture(filePath, type);
		
	return s_Textures[name];
	
}

Shader ResourceManager::LoadShader(const std::string filePath, const std::string name)
{
	if (s_Shaders.find(name) == s_Shaders.end())
		s_Shaders[name] = Shader(filePath);

	return s_Shaders[name];
}

void ResourceManager::Clear() const
{
	for (auto& it : s_Textures)
		it.second.Delete();

	for (auto& it : s_Shaders)
		it.second.Delete();
}

Texture ResourceManager::GetTexture(const std::string name)
{
	return s_Textures[name];
}

Shader ResourceManager::GetShader(const std::string name)
{
	if (s_Shaders.contains(name))
		return s_Shaders.at(name);
	else {
		std::cout << std::format("ResourceManager: Shader {} not loaded", name);
		return Shader();
	}
}
