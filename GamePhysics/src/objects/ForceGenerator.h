#pragma once
#include "PhysicObject.h"

class ForceGenerator
{
public:
	ForceGenerator(){};
	ForceGenerator(float force);
	~ForceGenerator() {};

	inline void SetAppliedForce(float force) { m_appliedForce = force; }
	inline float GetAppliedForce() const { return m_appliedForce; }

	virtual void ApplyForceForObject (PhysicObject* obj) = 0;

protected:
	float m_appliedForce = 9.81f;
};
