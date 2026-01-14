#include "OrbitalElement.h"
#include "IvyyyMathF.h"
#include <cmath>
#include "IvyyyDraw.h"
#include "IvyyyTime.h"
#include <IvyyyPhysic.h>

void OrbitalElement::Update()
{
	CalculateOrbit();

	if (m_soi != nullptr)
	{
		Vector3 posOffset = m_soi->GetTransform()->GetPosition();

		for (int i = 1; i < 64; ++i)
			Draw::AddLine (posOffset + m_orbitPath[i-1], posOffset + m_orbitPath[i], Color::White);

		Draw::AddLine(posOffset + m_orbitPath[0], posOffset + m_orbitPath[63], Color::White);
	}
}

void OrbitalElement::SetOrbitalData(const OrbitalElementData& orbitData, const PhysicObject* soi)
{
	m_orbitalElementData = orbitData;
	m_orbitData = OrbitalData (orbitData);
	m_soi = soi;

	if (m_soi != nullptr)
	{
		float mass = soi->GetMass();
		float gm = IvyyyPhysic::GravitationalConstant() * mass;
		m_orbitData.n = std::sqrtf (gm / (m_orbitalElementData.a * m_orbitalElementData.a * m_orbitalElementData.a));
		m_orbitData.t = 2.f * float(M_PI) / m_orbitData.n;
	}

	CalculateOrbitPath();
}

void OrbitalElement::CalculateOrbit()
{
	if (m_soi == nullptr || m_orbitalElementData.e >= 1.0f)
		return;

	Vector3 pos = m_soi->GetTransform()->GetPosition() + CalculateOrbitalPositionAtTime (m_timer);

	transform->SetPosition(pos);

	// --- 6. Advance time ---
	m_timer += Time::DeltaTime();
}

void OrbitalElement::CalculateOrbitPath()
{
	float timeStep = m_orbitData.t / 64;
	float time = 0.f;
	for (int i = 0; i < 64; ++i)
	{
		m_orbitPath[i] = CalculateOrbitalPositionAtTime (time);
		time += timeStep;
	}
}

float OrbitalElement::CalculateEccentricAnomaly (float time)
{
	float M = (m_orbitalElementData.m0 * MathF::Deg2Rad) + m_orbitData.n * time;

	// Wrap into [0, 2?]
	M = std::fmod(M, 2.0f * float(M_PI));
	if (M < 0.0f)
		M += 2.0f * float(M_PI);

	// --- 2. Solve Kepler's equation E - e*sin(E) = M ---
	float E = M; // initial guess
	const float e = m_orbitalElementData.e;

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

Vector3 OrbitalElement::CalculateOrbitalPositionAtTime(float time)
{
	float eccentricAnomaly = CalculateEccentricAnomaly(time);

	// --- 3. Position in ORBITAL PLANE (XY, Z = 0) ---
	float a = m_orbitalElementData.a;
	float e = m_orbitalElementData.e;

	Vector3 orbitalPosition(
		a * (std::cos(eccentricAnomaly) - e),
		a * std::sqrt(1.0f - e * e) * std::sin(eccentricAnomaly),
		0.0f
	);

	// --- 5. Rotate into world space ---
	Vector3 pos = m_orbitData.orientation * orbitalPosition;

	return pos;
}
