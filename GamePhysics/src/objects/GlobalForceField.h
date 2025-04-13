#pragma once

#include "GameObject.h"
#include "objects/PhysicObject.h"

class GlobalForceField
	: public GameObject
	, public PhysicObject
{
public:
	GlobalForceField();
	GlobalForceField(float force);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override {};

	inline void SetForce (float force) {m_force = force;}
	float GetForce() const {return m_force;}

protected:
	float m_force = 9.81f;

	// Inherited via PhysicObject
	void ResolveCollision(PhysicObject* obj) override;
};