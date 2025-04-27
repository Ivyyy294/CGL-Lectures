#include "Planet.h"
#include<core/Draw.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/vector_angle.hpp>

float Planet::m_ScaleOneTo = 1.0f;
float Planet::m_universalGravitationalConstant = 1.0f;

Planet::Planet(float radius, float mass, ImColor color)
 : Circle (glm::vec2(0.0f, 0.0f), radius)
{
	SetMass (mass);
	m_color = color;
}

void Planet::ApplyForceForObject(PhysicObject* obj)
{
	if (Planet* planet2 = dynamic_cast<Planet*>(obj))
	{
		if (planet2 == this)
			return;

		glm::vec2 diff = m_position - obj->GetPosition();
		glm::vec2 direction = glm::normalize(diff);
		float distance = glm::dot(direction, diff);

		float force = m_universalGravitationalConstant * ((GetMass() * planet2->GetMass()) / std::pow(distance, 2.0f));

		glm::vec2 forceVec = direction * force;

		obj->ApplyForce(forceVec);
	}
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

