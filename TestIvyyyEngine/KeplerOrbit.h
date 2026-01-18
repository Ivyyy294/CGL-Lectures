#pragma once

#include "OrbitalElementData.h"
#include "OrbitalData.h"

class KeplerOrbit
{
public:
	static OrbitalData CallculateOrbitalData (const OrbitalElementData& orbitalElement, float parentMass);

	static Vector3 CalculateOrbitalPositionAtTime(const OrbitalElementData& orbitalElement, const OrbitalData& orbitalData, float time);

private:
	static float CalculateEccentricAnomaly(const OrbitalElementData& orbitalElement, const OrbitalData& orbitalData, float time);
};

