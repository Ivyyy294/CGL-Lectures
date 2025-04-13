#pragma once

#include "Circle.h"
#include "Wall.h"
#include "PhysicObject.h"

class BouncingBall
	: public Circle, public PhysicObject
{
public:
	BouncingBall(glm::vec2 pos, float radius, bool IsStatic = false);
	BouncingBall(glm::vec2 pos, float radius, float mass, float bounce, bool IsStatic = false);

	virtual void Update(float deltaTime) override;

	float GetBounce() const {return m_bounce;}

private:
	void ResolveCollision(PhysicObject* obj) override;
	void ResolveWall(Wall* wall);
	void ResolveCollision(BouncingBall* circle);

	void ApplyBounce(glm::vec2 impulse);

	float m_bounce = 0.5f;
};