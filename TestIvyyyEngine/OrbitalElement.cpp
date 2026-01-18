#include "OrbitalElement.h"
#include "IvyyyMathF.h"
#include <cmath>
#include "IvyyyDraw.h"
#include "IvyyyTime.h"
#include <IvyyyPhysic.h>
#include "KeplerOrbit.h"

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
	m_soi = soi;

	m_orbitData = KeplerOrbit::CallculateOrbitalData (orbitData, m_soi != nullptr ? m_soi->GetMass() : -1.f);

	CalculateOrbitPath();
}

void OrbitalElement::CalculateOrbit()
{
	if (m_soi == nullptr || m_orbitalElementData.e >= 1.0f)
		return;

	Vector3 pos = m_soi->GetTransform()->GetPosition() + KeplerOrbit::CalculateOrbitalPositionAtTime (m_orbitalElementData, m_orbitData, m_timer);

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
		m_orbitPath[i] = KeplerOrbit::CalculateOrbitalPositionAtTime (m_orbitalElementData, m_orbitData, time);
		time += timeStep;
	}
}

