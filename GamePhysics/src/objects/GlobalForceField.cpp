#include "GlobalForceField.h"
#include "Physics.h"

GlobalForceField::GlobalForceField()
	: ForceField (9.81)
{
	SetStatic (true);
	SetTrigger(true);
}

GlobalForceField::GlobalForceField(float force)
: ForceField (force)
{
}

Collision GlobalForceField::TestCollision(PhysicObject* collider)
{
	Collision collision;

	glm::vec2 diff = m_position - collider->GetPosition();
	glm::vec2 normal = glm::normalize (diff);
	float length = glm::dot (normal, diff);

	collision.m_collision = true;
	collision.m_normal = normal;
	collision.m_interrsectionDepth = length;

	return collision;
}

void GlobalForceField::OnTriggerEnter(PhysicObject* obj)
{
	obj->ApplyForce (glm::vec2(0.0f, m_appliedForce * -1.0f * obj->GetMass()));
}
