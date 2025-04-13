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
	glm::vec2 GetForceForObject(PhysicObject* obj) override;
};
