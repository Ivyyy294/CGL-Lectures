#include "OrbitalElement.h"
#include "IvyyyMathF.h"
#include <cmath>
#include "IvyyyDraw.h"
#include "IvyyyTime.h"
#include <IvyyyPhysic.h>

void OrbitalElement::Update()
{
	CalculateOrbit();
}

void OrbitalElement::SetOrbitalData(const OrbitalElementData& orbitData, const PhysicObject* soi)
{
	m_orbitalElementData = orbitData;
	m_orbitData = OrbitalData (orbitData);
	m_soi = soi;

	if (m_soi != nullptr)
	{
		float gm = IvyyyPhysic::GravitationalConstant() * soi->GetMass();
		m_orbitData.n = std::sqrtf (gm / (m_orbitalElementData.a * m_orbitalElementData.a * m_orbitalElementData.a));
	}
}

void OrbitalElement::CalculateOrbit()
{
	if (m_soi == nullptr)
		return;

	// --- 1. Advance mean anomaly ---
	float meanAnomaly = m_orbitalElementData.m0 + m_orbitData.n * m_timer;

	// Elliptical only
	if (m_orbitalElementData.e >= 1.0f)
		return;

	// --- 2. Solve Kepler equation ---
	float eccentricAnomaly = meanAnomaly;
	for (int iter = 0; iter < 10; ++iter)
	{
		float f = eccentricAnomaly
			- m_orbitalElementData.e * std::sin(eccentricAnomaly)
			- meanAnomaly;
		float fp = 1.0f - m_orbitalElementData.e * std::cos(eccentricAnomaly);
		eccentricAnomaly -= f / fp;
	}

	// --- 3. Position in ORBITAL PLANE (XY, Z = 0) ---
	float a = m_orbitalElementData.a;
	float e = m_orbitalElementData.e;

	Vector3 orbitalPosition(
		a * (std::cos(eccentricAnomaly) - e),
		a * std::sqrt(1.0f - e * e) * std::sin(eccentricAnomaly),
		0.0f
	);

	// --- 5. Rotate into world space ---
	Vector3 center = m_soi->GetTransform()->GetPosition() + m_orbitData.center;
	Vector3 pos = center + m_orbitData.orientation * orbitalPosition;

	transform->SetPosition(pos);

	// --- 6. Advance time ---
	m_timer += Time::DeltaTime();
}

void OrbitalElement::CalculateOrbitPath()
{
	//Vector3 u = (m_center - transform->GetPosition()).Normalized();
	//Vector3 v = u.Cross(m_orbitalPlaneNormal);

	//const float TWO_PI = 2.0 * float(M_PI);

	//for (int i = 0; i < 16; ++i)
	//{
	//	float theta = TWO_PI * i / 16;

	//	Vector3 point =
	//		m_center +
	//		v * (m_orbitData.a * std::cosf(theta)) +
	//		u * (m_b * std::sinf(theta));

	//	m_orbitPath[i] = point;
	//}
}
