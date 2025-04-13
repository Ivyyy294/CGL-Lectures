#include "CircleForceField.h"
#include "BouncingBall.h"
#include "Physics.h"

CircleForceField::CircleForceField(glm::vec2 pos, float radius, float gravity)
	: Circle (pos, radius)
	, m_gravity (gravity)
{
	m_color = ImColor(255, 255, 0, 255);
	SetStatic (true);
}

void CircleForceField::Update(float deltaTime)
{
}

void CircleForceField::ResolveCollision(PhysicObject* obj)
{
	if (BouncingBall* bb = dynamic_cast<BouncingBall*>(obj))
	{
		glm::vec2 direction = m_circlePosition - bb->Position();
		float distance = glm::length(direction);

		if (distance <= m_circleRadius)
		{
			float factor = m_gravity * std::pow(Physics::m_deltaTime, 2);
			glm::vec2 force = glm::normalize (direction) * factor;
			obj->ApplyForce (force);
		}
	}
}
