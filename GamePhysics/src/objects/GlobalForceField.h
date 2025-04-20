#pragma once

#include "GameObject.h"
#include "ForceField.h"

class GlobalForceField
	: public GameObject
	, public ForceField
{
public:
	GlobalForceField();
	GlobalForceField(float force);

	virtual void Update(float deltaTime) override {};
	virtual void Draw() override {};

protected:

	// Inherited via ForceField
	void ResolveCollision (PhysicObject* obj) override;
};