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

void Physics::RunForPhysicObject(PhysicObject* obj, float deltaTime)
{
	RunPhysicForObject (deltaTime, obj);
	RunCollisionsForObject(deltaTime, obj);
}

void Physics::RunPhysicForObject(float deltaTime, PhysicObject* obj)
{
	if (obj->IsStatic())
		return;
	
	glm::vec2 force = glm::vec2 (0.0f, 0.0f);

	for (size_t j = 0; j < m_forceFields.size(); ++j)
		force += m_forceFields[j]->GetForceForObject (obj);

	obj->m_velocity += force * deltaTime;

	if (GameObject* gameObj = dynamic_cast<GameObject*>(obj))
		gameObj->m_position += obj->m_velocity * deltaTime;
}

void Physics::RunCollisionsForObject(float deltaTime, PhysicObject* obj, int startIndex)
{
	for (int i = startIndex; i < m_physicObjects.size(); ++i)
	{
		PhysicObject* obj2 = m_physicObjects[i];

		if (obj == obj2)
			continue;
		else
		{
			if (obj->IsTrigger() || obj2->IsTrigger())
				continue;

			ResolveCollision(obj, obj2);
			ResolveCollision(obj2, obj);
		}
	}
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


