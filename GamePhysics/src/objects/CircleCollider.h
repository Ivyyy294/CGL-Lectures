#pragma once
#include "PhysicObject.h"
#include "Wall.h"

class CircleCollider
	: public PhysicObject
{
public:
	CircleCollider (const float radius);
	~CircleCollider (){};

	inline void SetRadius (const float radius) { m_radius = radius; }
	inline const float& Radius() const { return m_radius; }

protected:
	float m_radius = 1.0f;
};