#pragma once
#include <string>

#include <mutex>
#include <unordered_map>
#include <GL/Core/Texture.h>
#include <GL/Core/Shader.h>

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

	Texture LoadTexture(const std::string filePath, const std::string name, TextureType type);
	Shader LoadShader(const std::string filePath, const std::string name);
	void Clear() const;
	
	Texture GetTexture(const std::string name);
	Shader GetShader(const std::string name);
};


class ManagedResource
{
public:
	virtual ~ManagedResource() = default;;
};

class ResourceContainer
{
private:
	std::unordered_map<std::string, std::shared_ptr<ManagedResource>> resources_;

public:
	void Add(std::shared_ptr<ManagedResource> obj, const std::string name)
	{
		auto it = resources_.find(name);
		if (it != resources_.end()) {
			std::cout << "Resource of name " << name << " already exist\n";
			return;
		}
		resources_[name] = obj;
	}

	std::shared_ptr<ManagedResource> Get(const std::string name)
	{
		auto it = resources_.find(name);
		if (it == resources_.end()) {
			std::cout << "Cannot find resource of name " << name << std::endl;
			return nullptr;
		}
		return resources_[name];
	}
};

class ResourceManager
{
private:
	std::unordered_map<std::string, ResourceContainer> containers_;

public:
	
	template <typename T>
	void Add(std::shared_ptr<T> obj, const std::string name)
	{
		auto type = typeid(T).name();
		auto it = containers_.find(type);
		containers_[type].Add(obj, name);
	}

	template <typename T>
	std::shared_ptr<T> Get(const std::string name)
	{
		auto type = typeid(T).name();
		auto it = containers_.find(type);
		if (it == containers_.end()) {
			std::cout << "No resources of type " << type << " available\n";
			return nullptr;
		}
		return it->second.Get(name);
	}
};
/*
	TODO: Continue creating generic resource manager
		- Now adding new resources is contained in manager
		- Move that functionality to resource itself
		- This might not be such a good idea?
		- Separate resource loader?
			-
*/
