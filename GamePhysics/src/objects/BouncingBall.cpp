#include "BouncingBall.h"

BouncingBall::BouncingBall(glm::vec2 pos, float radius, bool IsStatic)
: Circle (pos, radius)
{
	SetStatic (IsStatic);
}

BouncingBall::BouncingBall(glm::vec2 pos, float radius, float mass, float bounce, bool IsStatic)
	: Circle(pos, radius)
	, m_bounce (bounce)
{
	SetMass (mass);
	SetStatic(IsStatic);
}

void BouncingBall::Update(float deltaTime)
{
	if (m_static)
		return;
}

void BouncingBall::ResolveCollision(PhysicObject* obj)
{
	if (Wall* wall = dynamic_cast<Wall*>(obj))
		ResolveWall(wall);
	else if (BouncingBall* bb = dynamic_cast<BouncingBall*>(obj))
		ResolveCollision (bb);
}

void BouncingBall::ResolveWall(Wall* wall)
{
	glm::vec2 d = wall->End() - wall->Start();
	glm::vec2 f = m_position - wall->Start();

	// 2D Kreuzprodukt: d.x * f.y - d.y * f.x
	float cross = d.x * f.y - d.y * f.x;
	float distance = std::abs(cross) / glm::length(d);

	if (distance > m_circleRadius)
		return;

	glm::vec2 v = wall->Start() - m_position;
	float t = -glm::dot(v, d) / glm::dot(d, d); // Orthogonaler Lotfußpunkt auf der Geraden
	glm::vec2 closestPoint = wall->Start() + t * d;

	glm::vec2 fromCenter = closestPoint - m_position;

	// Punkt auf Kreis im gleichen Lot-Vektor, aber auf Radiuslänge skaliert
	glm::vec2 pointOnCircle = m_position + glm::normalize(fromCenter) * m_circleRadius;

	m_position += closestPoint - pointOnCircle;

	glm::vec2 force = glm::normalize(m_position - closestPoint) * (glm::length(m_velocity));

	ApplyBounce(force);
}

void BouncingBall::ResolveCollision(BouncingBall* circle)
{
	glm::vec2 direction = m_position - circle->m_position;
	float distance = glm::length(direction);
	float min_distance = Radius() + circle->Radius();

	if (distance <= 0.001f)
	{
		distance = min_distance * 0.99f;
		direction.x = rand();
		direction.y = rand();
	}

	if (distance < min_distance)
	{
		m_position += glm::normalize(direction) * (min_distance - distance);

		float speed = glm::length(circle->m_velocity);

		if (speed <= 0.0f)
			speed = glm::length(m_velocity);

		glm::vec2 impulse = glm::normalize (direction) * speed;

		ApplyBounce(impulse);
	}
}

void BouncingBall::ApplyBounce(glm::vec2 impulse)
{
	m_velocity = m_velocity * (1.0f - glm::clamp (m_bounce, 0.0f, 1.0f));
	//m_velocity = m_velocity * 0.1f;
	ApplyImpulse(impulse);
}
