#include "KeplerOrbit.h"
#include "IvyyyPhysic.h"
#include <cmath>
#include "IvyyyMathF.h"

OrbitalData KeplerOrbit::CallculateOrbitalData(const OrbitalElementData& orbitalElement, float parentMass)
{
	OrbitalData data = OrbitalData(orbitalElement);

	if (parentMass > 0.0f)
	{
		float gm = IvyyyPhysic::GravitationalConstant() * parentMass;
		data.n = std::sqrtf(gm / (orbitalElement.a * orbitalElement.a * orbitalElement.a));
		data.t = 2.f * float(M_PI) / data.n;
	}

	return data;
}

float KeplerOrbit::CalculateEccentricAnomaly(const OrbitalElementData& orbitalElement, const OrbitalData& orbitalData, float time)
{
	float M = (orbitalElement.m0 * MathF::Deg2Rad) + orbitalData.n * time;

	// Wrap into [0, 2?]
	M = std::fmod(M, 2.0f * float(M_PI));
	if (M < 0.0f)
		M += 2.0f * float(M_PI);

	// --- 2. Solve Kepler's equation E - e*sin(E) = M ---
	float E = M; // initial guess
	const float e = orbitalElement.e;

	for (int iter = 0; iter < 10; ++iter)
	{
		float f = E - e * std::sin(E) - M;
		float fp = 1.0f - e * std::cos(E);
		E -= f / fp;
	}

	// Wrap E into [0, 2?]
	E = std::fmod(E, 2.0f * float(M_PI));
	if (E < 0.0f)
		E += 2.0f * float(M_PI);

	return E;
}

Vector3 KeplerOrbit::CalculateOrbitalPositionAtTime(const OrbitalElementData& orbitalElement, const OrbitalData& orbitalData, float time)
{
	float eccentricAnomaly = CalculateEccentricAnomaly(orbitalElement, orbitalData, time);

	// --- 3. Position in ORBITAL PLANE (XY, Z = 0) ---
	float a = orbitalElement.a;
	float e = orbitalElement.e;

	Vector3 orbitalPosition(
		a * (std::cos(eccentricAnomaly) - e),
		a * std::sqrt(1.0f - e * e) * std::sin(eccentricAnomaly),
		0.0f
	);

	// --- 5. Rotate into world space ---
	Vector3 pos = orbitalData.orientation * orbitalPosition;

	return pos;
}