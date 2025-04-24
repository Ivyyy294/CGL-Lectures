#include "Planet.h"
#include<core/Draw.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/vector_angle.hpp>

float Planet::m_ScaleOneTo = 1.0f;

Planet::Planet(float radius, float mass, ImColor color)
 : Circle (glm::vec2(0.0f, 0.0f), radius)
{
	SetMass (mass);
	m_color = color;
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

