#pragma once
#include "ParticleCollision.h"

class ParticleCollisionDetector
{
public:
	static ParticleCollision TestCollision(PhysicObject* obj1, PhysicObject* obj2);
};