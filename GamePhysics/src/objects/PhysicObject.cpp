#include "PhysicObject.h"

PhysicObject::PhysicObject()
{
}

PhysicObject::~PhysicObject()
{
}

void PhysicObject::ApplyForce(glm::vec2 force)
{
	if (m_static)
		return;

	m_velocity += force;
}

void PhysicObject::ApplyImpulse(glm::vec2 force)
{
	if (m_static)
		return;

	m_velocity = force / std::max (1.0f, m_mass);
}
