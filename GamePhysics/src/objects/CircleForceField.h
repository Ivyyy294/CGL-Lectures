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

	virtual void Update(float deltaTime) override;

private:

	// Inherited via ForceField
	void ResolveCollision (PhysicObject* obj) override;
};
