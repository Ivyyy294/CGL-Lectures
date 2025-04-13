#include "CircleForceField.h"
#include "BouncingBall.h"
#include "Physics.h"

CircleForceField::CircleForceField(glm::vec2 pos, float radius, float gravity)
	: Circle (pos, radius)
	, ForceField (gravity)
{
	m_color = ImColor(255, 255, 0, 255);
}

void CircleForceField::Update(float deltaTime)
{
}

glm::vec2 CircleForceField::GetForceForObject(PhysicObject* obj)
{
	glm::vec2 force (0.0, 0.0);

	if (BouncingBall* bb = dynamic_cast<BouncingBall*>(obj))
	{
		glm::vec2 direction = m_position - bb->GetPosition();
		float distance = glm::length(direction);

		if (distance <= m_circleRadius)
			force = glm::normalize (direction) * m_force;
	}

	return force;
}
