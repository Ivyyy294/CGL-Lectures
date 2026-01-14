#pragma once

#include <IvyyyVector3.h>
#include <IvyyyQuaternion.h>
#include "OrbitalElementData.h"

using namespace Ivyyy;

struct OrbitalData
{
	Vector3 center;
	Quaternion orientation;
	Vector3 periapsis;

	float c = 0.f;
	float b = 0.f;
	float t = 0.f;

	//mean motion
	float n = 0.f;

	OrbitalData(){};
	OrbitalData (const OrbitalElementData& data);
};

