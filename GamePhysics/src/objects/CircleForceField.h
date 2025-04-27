#pragma once
#include "Circle.h"
#include "objects/ForceGenerator.h"

class CircleForceField
	: public Circle
	, public ForceGenerator
{
public:
	CircleForceField (glm::vec2 pos, float radius, float gravity);
	~CircleForceField(){};

	void ApplyForceForObject(PhysicObject* obj) final;
};
