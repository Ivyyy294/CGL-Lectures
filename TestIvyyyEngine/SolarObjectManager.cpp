#include "SolarObjectManager.h"
#include "IvyyyPhysic.h"
#include <cmath>
#include "KeplerOrbit.h"
#include "IvyyyDraw.h"
#include "IvyyyTime.h"

void SolarObjectManager::Start()
{
	InitSolarObject (m_root, -1.f);
}

void SolarObjectManager::Update()
{
	UpdateOrbit (m_root, Vector3::Zero, m_timer);
	DrawOrbit (m_root, Vector3::Zero);

	m_timer += Time::DeltaTime();
}

void SolarObjectManager::InitSolarObject(SolarObject& so, float parentMass)
{
	so.orbitalData = KeplerOrbit::CallculateOrbitalData (so.orbitalElement, parentMass);

	CalculateOrbitPath (so);

	for (size_t i = 0; i < so.children.size(); i++)
		InitSolarObject (so.children[i], so.planetData.mass);
}

void SolarObjectManager::CalculateOrbitPath(SolarObject& so)
{
	float timeStep = so.orbitalData.t / 64;
	float time = 0.f;
	for (int i = 0; i < 64; ++i)
	{
		so.orbitPath[i] = KeplerOrbit::CalculateOrbitalPositionAtTime(so.orbitalElement, so.orbitalData, time);
		time += timeStep;
	}
}

void SolarObjectManager::DrawOrbit(SolarObject& so, const Vector3& posOffset)
{
	for (int i = 1; i < 64; ++i)
		Draw::AddLine(posOffset + so.orbitPath[i - 1], posOffset + so.orbitPath[i], so.planetData.color);

	Draw::AddLine(posOffset + so.orbitPath[0], posOffset + so.orbitPath[63], so.planetData.color);

	for (size_t i = 0; i < so.children.size(); i++)
		DrawOrbit(so.children[i], so.gameObject->transform.GetPosition());
}

void SolarObjectManager::UpdateOrbit(SolarObject& so, const Vector3& parentPos, const float timer)
{
	Vector3 newPos = parentPos;

	if (so.orbitalData.t > 0.f)
		newPos += KeplerOrbit::CalculateOrbitalPositionAtTime (so.orbitalElement, so.orbitalData, timer);
	
	so.gameObject->transform.SetPosition (newPos);

	for (size_t i = 0; i < so.children.size(); i++)
		UpdateOrbit(so.children[i], newPos, timer);
}
