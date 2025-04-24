#include "Planet.h"
#include<core/Draw.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/vector_angle.hpp>
#include "PlanetGravity.h"

float PlanetGravity::m_universalGravitationalConstant = 6.673f * std::pow (10.0f, -11.0f);

PlanetGravity::PlanetGravity(Planet* planet)
	: m_planet (planet)
{
	m_position = m_planet->GetPosition();
	SetStatic (true);
	SetTrigger (true);
}

void PlanetGravity::Update(float deltaTime)
{
	m_position = m_planet->GetPosition();
}

Collision PlanetGravity::TestCollision(PhysicObject* collider)
{
	Collision collision;

	glm::vec2 diff = m_position - collider->GetPosition();
	glm::vec2 normal = glm::normalize(diff);
	float length = glm::dot(normal, diff);

	collision.m_collision = true;
	collision.m_normal = normal;
	collision.m_interrsectionDepth = length;

	return collision;
}

void PlanetGravity::OnTriggerEnter(PhysicObject* obj, const Collision& collision)
{
	if (Planet* planet2 = dynamic_cast<Planet*>(obj))
	{
		if (planet2 == m_planet)
			return;

		glm::vec2 direction = collision.m_normal;
		float distance = collision.m_interrsectionDepth;

		float force = m_universalGravitationalConstant * ((m_planet->GetMass() * planet2->GetMass()) / std::pow(distance, 2.0f));

		glm::vec2 forceVec = direction * force;

		obj->ApplyForce(forceVec);
	}
}



