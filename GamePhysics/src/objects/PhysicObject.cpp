#include "PhysicObject.h"

std::vector <PhysicObject*> PhysicObject::m_physicObjects;

PhysicObject::PhysicObject()
{
	m_physicObjects.push_back (this);
}

PhysicObject::~PhysicObject()
{
	for (auto i = m_physicObjects.begin(); i != m_physicObjects.end(); i++)
	{
		if (*i == this)
		{
			m_physicObjects.erase (i);
			return;
		}
	}
}

void PhysicObject::ApplyForce(glm::vec2 force)
{
	m_velocity += force;
}

void PhysicObject::ApplyImpulse(glm::vec2 force)
{
	float length = glm::length(m_velocity);
	m_velocity += force;
	m_velocity = glm::normalize(m_velocity) * length;
}
