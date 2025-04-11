#pragma once

#include "GameObject.h"
#include "PhysicObject.h"

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
	float m_force = 0.981f;
	glm::vec3 m_forceThisFrame = glm::vec3 (0.0, 0.0, 0.0);

	// Inherited via PhysicObject
	void ResolveCollision(PhysicObject* obj) override;
};