#pragma once
#include <string>
#include <memory>

namespace Whegine
{
	template <typename T>
	std::shared_ptr<T> Load(const std::string filepath)
	{
		return std::make_shared<T>(new T(filepath));
	}
}