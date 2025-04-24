#pragma once

#include "PhysicObject.h"
#include "ForceField.h"

class GlobalForceField
	: public PhysicObject
	, public ForceField
{
public:
	GlobalForceField();
	GlobalForceField(float force);

	virtual void Update(float deltaTime) override {};
	virtual void Draw() override {};

private:
	Collision TestCollision(PhysicObject* collider) final;
	void OnTriggerEnter(PhysicObject* obj) final;
};