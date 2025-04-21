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

	m_impulse += force / m_mass;
}

void PhysicObject::ApplyForce(glm::vec2 force)
{
	if (m_static)
		return;

	m_force += force / m_mass;
}

glm::vec2 PhysicObject::Reflection(glm::vec2 direction, glm::vec2 normal)
{
	normal = glm::normalize (normal);
   return direction - 2.0f * glm::dot (direction, normal) * normal;
}

