#include "PhysicObject.h"

PhysicObject::PhysicObject()
{
}

PhysicObject::~PhysicObject()
{
}

void PhysicObject::ApplyImpulse(glm::vec2 force)
{
	if (m_static)
		return;

	m_velocity += force / m_mass;
}

