#include "Physics.h"
#include "GlobalForceField.h"

float Physics::m_deltaTime = 0.0f;
std::vector <PhysicObject*> Physics::m_physicObjects;

void Physics::Run()
{
   for (int i = 0; i < m_physicObjects.size(); ++i)
		RunForPhysicObject(m_physicObjects[i], i + 1);
}

void Physics::RunForPhysicObject(PhysicObject* obj, int startIndex)
{
	for (int i = startIndex; i < m_physicObjects.size(); ++i)
	{
		PhysicObject* obj2 = m_physicObjects[i];

		if (obj == obj2)
			continue;
		else
		{
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


