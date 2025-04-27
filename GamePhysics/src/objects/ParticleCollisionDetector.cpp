#include "ParticleCollisionDetector.h"
#include "CircleCollider.h"
#include "Wall.h"

ParticleCollision TestCollisionCircleCollider(CircleCollider* circle, CircleCollider* circle2)
{
	ParticleCollision collision;
	collision.obj1 = circle;
	collision.obj2 = circle2;

	glm::vec2 direction = circle->GetPosition() - circle2->GetPosition();
	float distance = glm::length(direction);

	float squareLength = glm::dot(direction, direction);
	float min_distance = circle->Radius() + circle2->Radius();
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

ParticleCollision TestCollisionCircleCollider(CircleCollider* circle, Wall* wall)
{
	ParticleCollision collision;
	collision.obj1 = circle;
	collision.obj2 = wall;

	float circleRadius = circle->Radius();
	glm::vec2 circlePos = circle->GetPosition();

	glm::vec2 wallStart = wall->Start();
	glm::vec2 directionWall = wall->GetDirection();
	glm::vec2 wallStartToCircle = circlePos - wallStart;
	glm::vec2 wallNormal = glm::normalize(glm::vec2(-directionWall.y, directionWall.x));

	float wallLength = wall->Length();
	float dot = glm::dot(directionWall, wallStartToCircle);

	//early exit if dot is out of bounds
	if (dot < -circleRadius || dot >(wallLength + circleRadius))
		return collision;

	//Check start point
	glm::vec2 diff = circlePos - wallStart;
	float distance = glm::length(diff);

	if (dot < 0.0f && distance < circleRadius)
		collision.m_collision = true;

	//Check end point
	if (!collision.m_collision)
	{
		glm::vec2 wallEnd = wall->End();

		diff = circlePos - wallEnd;
		distance = glm::length(diff);

		if (dot > wallLength && distance < circleRadius)
			collision.m_collision = true;
	}

	//Check point between start and end
	if (!collision.m_collision)
	{
		glm::vec2 posOnLine = wallStart + directionWall * dot;
		diff = circlePos - posOnLine;
		distance = glm::length(diff);

		if (dot >= 0.0f && dot <= wallLength && distance < circleRadius)
			collision.m_collision = true;
	}

	if (collision.m_collision)
	{
		if (distance == 0.0f)
			collision.m_normal = wallNormal;
		else
			collision.m_normal = glm::normalize(diff);

		collision.m_interrsectionDepth = circleRadius - distance;
	}

	return collision;
}

ParticleCollision TestCollisionCircleCollider(CircleCollider* circle, PhysicObject* obj2)
{
	if (CircleCollider* circle2 = dynamic_cast<CircleCollider*> (obj2))
		return TestCollisionCircleCollider(circle, circle2);
	else if (Wall* wall = dynamic_cast<Wall*> (obj2))
		return TestCollisionCircleCollider(circle, wall);
	return ParticleCollision();
}

ParticleCollision ParticleCollisionDetector::TestCollision(PhysicObject* obj1, PhysicObject* obj2)
{
	if (CircleCollider* circle = dynamic_cast <CircleCollider*> (obj1))
		return TestCollisionCircleCollider (circle, obj2);
	else if (CircleCollider* circle = dynamic_cast <CircleCollider*> (obj2))
		return TestCollisionCircleCollider(circle, obj1);

    return ParticleCollision();
}
