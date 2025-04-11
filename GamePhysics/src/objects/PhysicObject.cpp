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

	float length = glm::length(m_velocity);
	m_velocity += force;
	m_velocity = glm::normalize(m_velocity) * length;
}
