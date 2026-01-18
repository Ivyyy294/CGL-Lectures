#pragma once
#include "IvyyyComponent.h"
#include "SolarObject.h"

using namespace Ivyyy;

class SolarObjectManager :
    public Component
{
//Variables
private:
	SolarObject m_root;
	float m_timer = 0.f;
//Methods
public:
	void Start() override;
	void Update() override;

	void SetSolarObject (const SolarObject& root) {m_root = root;}

private:
	void InitSolarObject (SolarObject& so, float parentMass);
	void CalculateOrbit(SolarObject& so);
	void CalculateOrbitPath(SolarObject& so);
	void DrawOrbit(SolarObject& so, const Vector3& posOffset);
	void UpdateOrbit (SolarObject& so, const Vector3& parentPos, const float timer);
};

