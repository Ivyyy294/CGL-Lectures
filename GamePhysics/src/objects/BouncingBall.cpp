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

Collision BouncingBall::TestCollision(PhysicObject* obj)
{
	if (Wall* wall = dynamic_cast<Wall*>(obj))
		return TestCollision (wall);

	return Collision();
}

Collision BouncingBall::TestCollision(BouncingBall* obj)
{
	glm::vec2 direction = m_position - obj->m_position;
	float distance = glm::length(direction);

	float squareLength = glm::dot(direction, direction);
	float min_distance = Radius() + obj->Radius();
	float intersectionDepth = distance - min_distance;

	//resolve perfectly overlapping balls
	if (distance <= 0.001f)
	{
		distance = min_distance * 0.99f;
		direction.x = rand();
		direction.y = rand();
	}

	if (distance <= min_distance)
		return Collision {true, glm::normalize(direction), min_distance - distance};

	return Collision();
}

Collision BouncingBall::TestCollision(Wall* wall)
{
	Collision result;

	glm::vec2 wallStart = wall->Start();
	glm::vec2 directionWall = wall->GetDirection();
	glm::vec2 wallStartToCircle = m_position - wallStart;
	float wallLength = wall->Length();
	float dot = glm::dot(directionWall, wallStartToCircle);

	//early exit if dot is out of bounds
	if (dot < -m_circleRadius || dot >(wallLength + m_circleRadius))
		return result;

	//Check start point
	glm::vec2 diff = m_position - wallStart;
	float distance = glm::length(diff);

	if (dot < 0.0f && distance < m_circleRadius)
	{
		result.m_collision = true;
		result.m_normal = glm::normalize(diff);
		result.m_interrsectionDepth = m_circleRadius - distance;
		return result;
	}

	//Check end point
	glm::vec2 wallEnd = wall->End();

	diff = m_position - wallEnd;
	distance = glm::length(diff);

	if (dot > wallLength && distance < m_circleRadius)
	{
		result.m_collision = true;
		result.m_normal = glm::normalize(diff);
		result.m_interrsectionDepth = m_circleRadius - distance;
		return result;
	}

	//Check point between start and end
	glm::vec2 posOnLine = wallStart + directionWall * dot;
	diff = m_position - posOnLine;
	distance = glm::length(diff);

	if (dot >= 0.0f && dot <= wallLength && distance < m_circleRadius)
	{
		result.m_collision = true;
		result.m_normal = glm::normalize (diff);
		result.m_interrsectionDepth = m_circleRadius - distance;
		return result;
	}

	return result;
}

void BouncingBall::ResolveCollision(PhysicObject* obj)
{
	if (Wall* wall = dynamic_cast<Wall*>(obj))
		ResolveWall(wall);
	else if (BouncingBall* bb = dynamic_cast<BouncingBall*>(obj))
		ResolveBall (bb);
}

void BouncingBall::ResolveWall(Wall* wall)
{
	glm::vec2 wallStart = wall->Start();
	glm::vec2 directionWall = wall->GetDirection();
	glm::vec2 wallStartToCircle = m_position - wallStart;
	float wallLength = wall->Length();
	float dot = glm::dot(directionWall, wallStartToCircle);

	//early exit if dot is out of bounds
	if (dot < -m_circleRadius || dot > (wallLength + m_circleRadius))
		return;

	//Check start point
	glm::vec2 diff = m_position - wallStart;
	float distance = glm::length (diff);

	if (dot < 0.0f && distance < m_circleRadius)
	{
		ResolveWall(diff, distance);
		return;
	}

	//Check end point
	glm::vec2 wallEnd = wall->End();

	diff = m_position - wallEnd;
	distance = glm::length(diff);

	if (dot > wallLength && distance < m_circleRadius)
	{
		ResolveWall(diff, distance);
		return;
	}

	//Check point between start and end
	glm::vec2 posOnLine = wallStart + directionWall * dot;
	diff = m_position - posOnLine;
	distance = glm::length (diff);

	if (dot >= 0.0f && dot <= wallLength && distance < m_circleRadius)
	{
		ResolveWall(diff, distance);
		return;
	}
}

void BouncingBall::ResolveWall(const glm::vec2 diff, const float distance)
{
	glm::vec2 normal = glm::normalize(diff);

	m_position += normal * (m_circleRadius - distance);

	Reflect(normal);
}

void BouncingBall::ResolveBall(BouncingBall* circle)
{
	glm::vec2 direction = m_position - circle->m_position;
	float distance = glm::length(direction);

	float squareLength = glm::dot(direction, direction);
	float min_distance = Radius() + circle->Radius();
	float intersectionDepth = distance - min_distance;

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
		Reflect (direction);
	}
}

void BouncingBall::Reflect(glm::vec2 direction)
{
	glm::vec2 impulse = Reflection(m_velocity, direction);
	m_velocity = glm::vec2(0.0, 0.0);
	ApplyImpulse(impulse);
}
