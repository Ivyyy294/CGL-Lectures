#pragma once

#include "IvyyyColor.h"
#include "OrbitalElement.h"

using namespace Ivyyy;

struct PlanetData
{
	float mass;
	float radius;
	Color color;
	bool isStatic;
	OrbitalElementData orbit;
	int trackLength;
	float lineSpacing;
};

