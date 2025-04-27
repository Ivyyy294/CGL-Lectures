#pragma once

#include "Circle.h"
#include "Wall.h"

class BouncingBall
	: public Circle
{
public:
	BouncingBall(float radius);
	BouncingBall(glm::vec2 pos, float radius, bool IsStatic = false);
	BouncingBall(glm::vec2 pos, float radius, float mass, bool IsStatic = false);
};