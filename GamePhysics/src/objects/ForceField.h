#pragma once
#include "PhysicObject.h"

class ForceField : public PhysicObject
{
public:
	ForceField(){};
	ForceField(float force);
	~ForceField() {};

	inline void SetForce(float force) { m_force = force; }
	inline float GetForce() const { return m_force; }

protected:
	float m_force = 9.81f;
};
