#include "CircleForceField.h"
#include "BouncingBall.h"

CircleForceField::CircleForceField(glm::vec2 pos, float radius, float gravity)
	: Circle (pos, radius)
	, m_gravity (gravity)
{
	m_color = ImColor(255, 255, 0, 255);
	SetStatic (true);
}

void CircleForceField::Update(float deltaTime)
{
	m_gravityThisFrame = m_gravity * std::pow(deltaTime, 2);
}

void CircleForceField::ResolveCollision(PhysicObject* obj)
{
	if (BouncingBall* bb = dynamic_cast<BouncingBall*>(obj))
	{
		glm::vec2 direction = m_circlePosition - bb->Position();
		float distance = glm::length(direction);

		if (distance <= m_circleRadius)
		{
			glm::vec2 force = glm::normalize (direction) * m_gravityThisFrame;
			obj->ApplyForce (force);
		}
	}
}
