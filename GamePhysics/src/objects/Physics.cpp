#include "Physics.h"

std::vector <PhysicObject*> Physics::m_physicObjects;
std::vector <ForceField*> Physics::m_forceFields;

void Physics::Run(float deltaTime)
{
   for (int i = 0; i < m_physicObjects.size(); ++i)
		RunPhysicForObject(deltaTime, m_physicObjects[i]);

	for (int i = 0; i < m_physicObjects.size(); ++i)
		RunCollisionsForObject(deltaTime, m_physicObjects[i], i + 1);
}

void Physics::RunPhysicForObject(float deltaTime, PhysicObject* obj)
{
	if (obj->IsStatic())
		return;
	
	//apply damping
	obj->m_velocity *= 1 - obj->m_linearDamping * deltaTime;

	glm::vec2 zero = glm::vec2(0.0f, 0.0f);

	obj->m_velocity += obj->m_impulse + obj->m_force * deltaTime;

	obj->m_impulse = zero;
	obj->m_force = zero;

	if (GameObject* gameObj = dynamic_cast<GameObject*>(obj))
		gameObj->m_position += obj->m_velocity * deltaTime;
}

void Physics::RunPhysicForSingleObject(PhysicObject* obj, float deltaTime)
{
	RunPhysicForObject(deltaTime, obj);
	RunCollisionsForObject(deltaTime, obj);
}

void Physics::RunCollisionsForObject(float deltaTime, PhysicObject* obj, int startIndex)
{
	for (int i = startIndex; i < m_physicObjects.size(); ++i)
	{
		PhysicObject* obj2 = m_physicObjects[i];

		//Prevent collision with self in case startIndex was not passed
		if (startIndex == 0 && obj == obj2)
			continue;

		Collision collision = obj->TestCollision (obj2);

		if (collision.m_collision)
			ResolveCollision (obj, obj2, collision);
		else
		{
			if (obj->IsTrigger() || obj2->IsTrigger())
				continue;

			ResolveCollision(obj, obj2);
			ResolveCollision(obj2, obj);
		}
	}
}

void Physics::ResolveCollision(PhysicObject* obj1, PhysicObject* obj2, const Collision& collison)
{
	float distance = collison.m_interrsectionDepth * 0.5f;
	((GameObject*)obj1)->m_position += collison.m_normal * distance;
	((GameObject*)obj2)->m_position += collison.m_normal * -distance;
}

void Physics::ResolveCollision(PhysicObject* obj1, PhysicObject* obj2)
{
	obj1->ResolveCollision (obj2);
}

void Physics::AddPhysicObject(PhysicObject* obj)
{
	m_physicObjects.push_back (obj);
}

void Physics::RemovePhysicObject(PhysicObject* obj)
{
	for (auto i = m_physicObjects.begin(); i != m_physicObjects.end(); i++)
	{
		if (*i == obj)
		{
			m_physicObjects.erase(i);
			return;
		}
	}
}

void Physics::AddForceField(ForceField* obj)
{
	m_forceFields.push_back (obj);
}

void Physics::RemoveForceField(ForceField* obj)
{
	for (auto i = m_forceFields.begin(); i != m_forceFields.end(); i++)
	{
		if (*i == obj)
		{
			m_forceFields.erase(i);
			return;
		}
	}
}


