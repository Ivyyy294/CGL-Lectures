#pragma once

#include "Circle.h"
#include "Wall.h"
#include "PhysicObject.h"

class BouncingBall
	: public Circle, public PhysicObject
{
public:
	BouncingBall(glm::vec2 pos, float radius, bool IsStatic = false);
	BouncingBall(glm::vec2 pos, float radius, float mass, bool IsStatic = false);

	virtual void Update(float deltaTime) override;

private:
	void ResolveCollision(PhysicObject* obj) override;
	
	void ResolveWall(Wall* wall);
	void ResolveWall(const glm::vec2 diff, const float distance);
	
	void ResolveBall(BouncingBall* circle);

	void Reflect (glm::vec2 direction);
};