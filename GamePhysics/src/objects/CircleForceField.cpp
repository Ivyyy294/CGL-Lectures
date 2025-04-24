#include "CircleForceField.h"
#include "BouncingBall.h"
#include "Physics.h"

CircleForceField::CircleForceField(glm::vec2 pos, float radius, float gravity)
	: Circle (pos, radius)
	, ForceField (gravity)
{
	if (gravity >= 0.0f)
		m_color = ImColor(255, 255, 0, 255);
	else
		m_color = ImColor(0, 0, 255, 255);

	SetStatic(true);
	SetTrigger (true);
}

void CircleForceField::OnTriggerEnter(PhysicObject* obj, const Collision& collision)
{
	glm::vec2 force(0.0, 0.0);

	if (BouncingBall* bb = dynamic_cast<BouncingBall*>(obj))
	{
		glm::vec2 direction = m_position - bb->GetPosition();
		float distance = glm::length(direction);

		if (distance <= m_radius + bb->Radius())
			force = glm::normalize(direction) * m_appliedForce;
	}

	obj->ApplyForce(force * obj->GetMass());
}
