#pragma once

#include "Entity.hpp"
#include <set>

class System
{
public:
	std::set<Entity> entities_;

	virtual void Update(const float dt) {};
	virtual void Render() {};
};