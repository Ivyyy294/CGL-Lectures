#pragma once
#include "PhysicObject.h"

class ForceField
{
public:
	ForceField(){};
	ForceField(float force);
	~ForceField() {};

	virtual glm::vec2 GetForceForObject (PhysicObject* obj) = 0;

	inline void SetForce(float force) { m_force = force; }
	inline float GetForce() const { return m_force; }

protected:
	float m_force = 9.81f;
};
