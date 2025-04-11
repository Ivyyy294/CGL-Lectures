#include "BouncingBall.h"

BouncingBall::BouncingBall(glm::vec2 pos, float radius, bool IsStatic)
: Circle (pos, radius)
{
	float vX = rand() % 10 * 0.001f;
	float vY = rand() % 10 * 0.001f;

	m_velocity = glm::vec2(vX, vY);

	SetStatic (IsStatic);
}

void BouncingBall::Update(float deltaTime)
{
	if (m_static)
		return;

	m_circlePosition += m_velocity;
}

void BouncingBall::ResolveCollision(PhysicObject* obj)
{
	if (Wall* wall = dynamic_cast<Wall*>(obj))
		ResolveCollision (wall);
	else if (BouncingBall* bb = dynamic_cast<BouncingBall*>(obj))
		ResolveCollision (bb);
}

void BouncingBall::ResolveCollision(Wall* wall)
{
	glm::vec2 start = wall->Start();
	glm::vec2 end = wall->End();
	glm::vec2 center = Position();
	float radius = Radius();

	float dx = end.x - start.x;
	float dy = end.y - start.y;

	float A = dx * dx + dy * dy;
	float B = 2 * ((start.x - center.x) * dx + (start.y - center.y) * dy);
	float C = (start.x - center.x) * (start.x - center.x) +
		(start.y - center.y) * (start.y - center.y) - radius * radius;

	float D = B * B - 4 * A * C; // Diskriminante

	if (D < 0) {
		return; // Keine Schnittpunkte
	}

	// Berechne die beiden möglichen Werte für t
	float t1 = (-B + sqrt(D)) / (2 * A);
	float t2 = (-B - sqrt(D)) / (2 * A);
	float t = 0.f;

	// Prüfe, ob mindestens ein t-Wert im Bereich [0,1] liegt
	if (t1 >= 0 && t1 <= 1)
		t = t1;
	else if (t2 >= 0 && t2 <= 1)
		t = t2;
	else
		return;

	glm::vec2 cp = wall->GetPointAtTime(t);
	glm::vec2 direction = center - cp;

	if (!IsStatic())
		ApplyImpulse(direction);
}

void BouncingBall::ResolveCollision(BouncingBall* circle)
{
	glm::vec2 direction = Position() - circle->Position();
	float distance = glm::length(direction);

	if (distance <= Radius() + circle->Radius())
	{
		float vel1 = glm::length(Velocity());
		float vel2 = glm::length(circle->Velocity());

		ApplyImpulse(direction);
	}
}
