#pragma once

#include "GameObject.h"
#include "ForceGenerator.h"

class GlobalForceField
	: public GameObject
	, public ForceGenerator
{
public:
	GlobalForceField();
	GlobalForceField(float force);

	void ApplyForceForObject(PhysicObject* obj) final;
};