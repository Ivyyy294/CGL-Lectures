#pragma once
#include "IvyyyComponent.h"
#include "OrbitalElementData.h"
#include "IvyyyPhysicObject.h"
#include "OrbitalData.h"

using namespace Ivyyy;

class OrbitalElement :
    public Component
{
	//Variables
	private:
		OrbitalElementData m_orbitalElementData;
		OrbitalData m_orbitData;
		const PhysicObject* m_soi {nullptr};

		Vector3 m_orbitPath [16];
		float m_timer = 0.f;

	//Methods
	public:
		void Update() override;
		void SetOrbitalData(const OrbitalElementData& orbitData, const PhysicObject* soi);

	private:
		void CalculateOrbit();
		void CalculateOrbitPath();
};

