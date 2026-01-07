#pragma once
struct OrbitalElementData
{
	//Semi major axis
	float a = 1.f;

	//Eccentricity
	float e = 1.f;

	//Inclination
	float i = 0.f;

	//Longitude of ascending node
	float o = 0.f;

	//Argument of periapsis
	float w = 0.f;

	//Mean anomaly at epoch
	float m0 = 0.f;
};

