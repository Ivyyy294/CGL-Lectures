#include "CircleForceField.h"
#include "BouncingBall.h"
#include "Physics.h"

CircleForceField::CircleForceField(glm::vec2 pos, float radius, float gravity)
	: Circle (pos, radius)
	, ForceGenerator (gravity)
{
	if (gravity >= 0.0f)
		m_color = ImColor(255, 255, 0, 255);
	else
		m_color = ImColor(0, 0, 255, 255);

	SetStatic(true);
	SetTrigger (true);
}

void CircleForceField::ApplyForceForObject(PhysicObject* obj)
{
	glm::vec2 force(0.0, 0.0);

	if (CircleCollider* bb = dynamic_cast<CircleCollider*>(obj))
	{
		glm::vec2 direction = m_position - bb->GetPosition();
		float distance = glm::length(direction);

		if (distance <= m_radius + bb->Radius())
			obj->ApplyForce (glm::normalize(direction) * m_appliedForce);
	}
	else if (obj != nullptr)
		obj->ApplyForce(force * obj->GetMass());
}

