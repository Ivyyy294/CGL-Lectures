#include "BouncingBall.h"

BouncingBall::BouncingBall(glm::vec2 pos, float radius, bool IsStatic)
: Circle (pos, radius)
{
	SetStatic (IsStatic);
}

BouncingBall::BouncingBall(glm::vec2 pos, float radius, float mass, bool IsStatic)
	: Circle(pos, radius)
{
	SetMass (mass);
	SetStatic(IsStatic);
}

