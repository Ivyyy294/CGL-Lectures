#pragma once

#include "Circle.h"
#include "Wall.h"
#include "PhysicObject.h"

class BouncingBall
	: public Circle, public PhysicObject
{
public:
	BouncingBall(glm::vec2 pos, float radius, bool IsStatic = false);

	virtual void Update(float deltaTime) override;

	inline void SetPosition (glm::vec2 pos) {m_circlePosition = pos;}

private:
	void ResolveCollision(PhysicObject* obj) override;
	void ResolveCollision(Wall* wall);
	void ResolveCollision(BouncingBall* circle);
};