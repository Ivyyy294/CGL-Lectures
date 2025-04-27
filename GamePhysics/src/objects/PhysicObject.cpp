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

	m_impulse += force * m_iMass;
}

void PhysicObject::ApplyForce(glm::vec2 force)
{
	if (m_static)
		return;

	m_force += force * m_iMass;
}

void PhysicObject::SetMass(float mass)
{
	m_mass = mass;
	m_iMass = 1.0f / mass;
}

void PhysicObject::SetLinearDamping(const float val)
{
	if (val < 0.0f)
		m_linearDamping = 0.0f;
	else
		m_linearDamping = val;
}

glm::vec2 PhysicObject::Reflection(glm::vec2 direction, glm::vec2 normal)
{
	normal = glm::normalize (normal);
   return direction - 2.0f * glm::dot (direction, normal) * normal;
}

glm::vec2 PhysicObject::GetForce()
{
	return m_velocity * m_mass;
}
