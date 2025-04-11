#pragma once
#include "Circle.h"
#include "PhysicObject.h"

class CircleForceField
	: public Circle
	, public PhysicObject
{
public:
	CircleForceField (glm::vec2 pos, float radius, float gravity);
	~CircleForceField(){};

	virtual void Update(float deltaTime) override;

private:
	void ResolveCollision (PhysicObject* obj) override;

	float m_gravity = 1.0;
	float m_gravityThisFrame = 0.0;
};
