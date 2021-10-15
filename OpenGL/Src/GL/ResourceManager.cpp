#include "ResourceManager.h"
#include <mutex>


ResourceManager* ResourceManager::s_Instance{ nullptr };
std::mutex ResourceManager::s_Mutex;

ResourceManager* ResourceManager::GetInstance()
{
	std::lock_guard<std::mutex> lock(s_Mutex);
	if (s_Instance == nullptr)
		s_Instance = new ResourceManager();

	return s_Instance;
}
