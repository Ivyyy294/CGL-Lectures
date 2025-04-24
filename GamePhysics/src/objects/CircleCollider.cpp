#include "CircleCollider.h"

CircleCollider::CircleCollider(const float radius)
	: m_radius (radius)
{
}

Collision CircleCollider::TestCollision(PhysicObject* collider)
{
	if (CircleCollider* cirle = dynamic_cast <CircleCollider*>(collider))
		return TestCollision(cirle);
	else if (Wall* wall = dynamic_cast<Wall*> (collider))
		return TestCollision(wall);
	else
		return Collision();
}

Collision CircleCollider::TestCollision(Wall* collider)
{
	Collision collision;

	glm::vec2 wallStart = collider->Start();
	glm::vec2 directionWall = collider->GetDirection();
	glm::vec2 wallStartToCircle = m_position - wallStart;
	glm::vec2 wallNormal = glm::normalize (glm::vec2 (-directionWall.y, directionWall.x));

	float wallLength = collider->Length();
	float dot = glm::dot(directionWall, wallStartToCircle);

	//early exit if dot is out of bounds
	if (dot < -m_radius || dot >(wallLength + m_radius))
		return collision;

	//Check start point
	glm::vec2 diff = m_position - wallStart;
	float distance = glm::length(diff);

	if (dot < 0.0f && distance < m_radius)
		collision.m_collision = true;

	//Check end point
	if (!collision.m_collision)
	{
		glm::vec2 wallEnd = collider->End();

		diff = m_position - wallEnd;
		distance = glm::length(diff);

		if (dot > wallLength && distance < m_radius)
			collision.m_collision = true;
	}

	//Check point between start and end
	if (!collision.m_collision)
	{
		glm::vec2 posOnLine = wallStart + directionWall * dot;
		diff = m_position - posOnLine;
		distance = glm::length(diff);

		if (dot >= 0.0f && dot <= wallLength && distance < m_radius)
			collision.m_collision = true;
	}

	if (collision.m_collision)
	{
		if (distance == 0.0f)
			collision.m_normal = wallNormal;
		else
			collision.m_normal = glm::normalize(diff);

		collision.m_interrsectionDepth = m_radius - distance;
	}

	return collision;
}

Collision CircleCollider::TestCollision(CircleCollider* collider)
{
	Collision collision;
	
	glm::vec2 direction = m_position - collider->m_position;
	float distance = glm::length(direction);

	float squareLength = glm::dot(direction, direction);
	float min_distance = Radius() + collider->Radius();
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
		direction = glm::normalize(direction);

		collision.m_collision = true;
		collision.m_interrsectionDepth = min_distance - distance;
		collision.m_normal = direction;
	}

	return collision;
}
