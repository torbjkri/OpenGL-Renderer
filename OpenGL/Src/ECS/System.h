#pragma once

#include "Entity.hpp"
#include <set>

class System
{
public:
	std::set<Entity> entities_;
};