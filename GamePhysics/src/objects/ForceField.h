#pragma once
#include "PhysicObject.h"

class ForceField
	: public PhysicObject
{
public:
	ForceField(){};
	~ForceField() {};

	virtual glm::vec2 GetEffectiveForceForObject (PhysicObject* obj, float time) = 0;
};
