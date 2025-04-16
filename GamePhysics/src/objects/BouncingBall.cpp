#include "BouncingBall.h"

BouncingBall::BouncingBall(glm::vec2 pos, float radius, bool IsStatic)
: Circle (pos, radius)
{
	SetStatic (IsStatic);
}

BouncingBall::BouncingBall(glm::vec2 pos, float radius, float mass, bool IsStatic)
	: Circle(pos, radius)
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
	glm::vec2 directionWall = wall->GetDirection();
	glm::vec2 wallStartToCircle = m_position - wall->Start();
	float dot = glm::dot (wall->GetDirection(), wallStartToCircle);

	glm::vec2 posOnLine = wall->Start() + directionWall * dot;

	float distance = glm::length (m_position - posOnLine);

	if (distance >= Radius()
	|| dot < 0.0f
	|| dot > wall->Length())
		return;

	glm::vec2 normal = glm::normalize (m_position - posOnLine);

	m_position += normal * (m_circleRadius - distance);

	glm::vec2 impulse = Reflection(m_velocity, normal);
	m_velocity = glm::vec2(0.0, 0.0);
	ApplyImpulse (impulse);
}

void BouncingBall::ResolveCollision(BouncingBall* circle)
{
	glm::vec2 direction = m_position - circle->m_position;
	float distance = glm::length(direction);
	float min_distance = Radius() + circle->Radius();

	//resolve perfectly overlapping balls
	if (distance <= 0.001f)
	{
		distance = min_distance * 0.99f;
		direction.x = rand();
		direction.y = rand();
	}

	if (distance <= min_distance)
	{
		direction = glm::normalize (direction);
		m_position += direction * (min_distance - distance);

		glm::vec2 impulse = Reflection(m_velocity, direction);
		m_velocity = glm::vec2(0.0, 0.0);
		ApplyImpulse(impulse);
	}
}

