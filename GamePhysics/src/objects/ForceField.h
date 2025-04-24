#pragma once
#include "PhysicObject.h"

class ForceField
{
public:
	ForceField(){};
	ForceField(float force);
	~ForceField() {};

	inline void SetAppliedForce(float force) { m_appliedForce = force; }
	inline float GetAppliedForce() const { return m_appliedForce; }

protected:
	float m_appliedForce = 9.81f;
};
