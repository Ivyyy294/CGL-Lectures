#pragma once
#include "Circle.h"
#include "objects/ForceField.h"

class CircleForceField
	: public Circle
	, public ForceField
{
public:
	CircleForceField (glm::vec2 pos, float radius, float gravity);
	~CircleForceField(){};

private:

	// Inherited via ForceField
	void OnTriggerEnter(PhysicObject* obj, const Collision& collision);
};
