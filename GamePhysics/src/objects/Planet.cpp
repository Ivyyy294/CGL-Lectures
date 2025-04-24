#include "Planet.h"
#include<core/Draw.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/vector_angle.hpp>

float Planet::m_universalGravitationalConstant = 6.673f * std::pow (10.0f, -11.0f);
float Planet::m_ScaleOneTo = 1.0f;

Planet::Planet(float radius, float mass, ImColor color)
: m_radius (radius)
, m_color (color)
{
	SetMass (mass);
}

Collision Planet::TestCollision(PhysicObject* collider)
{
	if (Planet* planet2 = dynamic_cast<Planet*>(collider))
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
	else
		return collider->TestCollision (collider);
}

void Planet::Draw()
{
	Draw::SetColor (m_color);

	float scaledRadius = m_radius * GetScale();
	glm::vec2 scaledPos = m_position * GetScale();

	Draw::Circle (scaledPos, scaledRadius, true);
}

float Planet::GetScale()
{
	return 1.0f / m_ScaleOneTo;
}

void Planet::OnCollisionEnter(PhysicObject* obj, const Collision& collision)
{
	//if (Planet* planet2 = dynamic_cast<Planet*>(obj))
	//{
	//	glm::vec2 direction = collision.m_normal;
	//	float distance = collision.m_interrsectionDepth;

	//	float force = m_universalGravitationalConstant * ((m_mass * planet2->m_mass) / std::pow(distance, 2.0f));

	//	glm::vec2 forceVec = glm::normalize(direction) * force;

	//	ApplyForce(forceVec);

	//	float min_distance = m_radius + planet2->m_radius;

	//	//only affect planet with less mass for now
	//	if (distance < min_distance && m_mass < planet2->m_mass)
	//	{
	//		if (distance <= 0.001f)
	//		{
	//			distance = 0.001f;
	//			direction = glm::normalize(glm::vec2(rand(), rand()));
	//		}
	//		else
	//			direction = glm::normalize(m_position - planet2->m_position);

	//		m_position += direction * (min_distance - distance);

	//		//kill velocity on impact
	//		m_velocity = glm::vec2(0.0f, 0.0f);
	//	}
	//}
}
