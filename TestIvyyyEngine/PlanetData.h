#pragma once

#include "IvyyyColor.h"
#include "OrbitalElement.h"

using namespace Ivyyy;

struct PlanetData
{
	float mass;
	float radius;
	Color color;
	std::vector<float> rings;
};

