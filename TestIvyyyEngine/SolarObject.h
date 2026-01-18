#pragma once
#include "PlanetData.h"
#include "OrbitalElementData.h"
#include <IvyyyGameObject.h>

struct SolarObject
{
	PlanetData planetData;
	OrbitalElementData orbitalElement;
	GameObject* gameObject;
	OrbitalData orbitalData;
	Vector3 orbitPath[64];

	std::vector<SolarObject> children;
};

