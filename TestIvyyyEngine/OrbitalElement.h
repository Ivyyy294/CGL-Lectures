#pragma once
#include "IvyyyComponent.h"
#include "OrbitalElementData.h"
#include "IvyyyPhysicObject.h"

using namespace Ivyyy;

class OrbitalElement :
    public Component
{
	//Variables
	private:
		OrbitalElementData m_orbitData;
		const PhysicObject* m_soi {nullptr};
		PhysicObject* m_rb {nullptr};

		Vector3 m_center;
		Vector3 m_orbitalPlaneNormal;
		Vector3 m_periapsisDir;
		float m_c = 0.f;
		float m_b = 0.f;
		float m_t = 0.f;

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

