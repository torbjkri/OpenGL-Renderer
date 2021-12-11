#pragma once

#include <bitset>

using ComponentType = std::uint8_t;

const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

struct Transform
{
	float scale;
	int translate;
};

struct Color
{
	float R;
	float G;
	float B;
};

