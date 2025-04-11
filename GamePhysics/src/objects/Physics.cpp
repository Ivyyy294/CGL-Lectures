#include "Physics.h"
#include "GlobalForceField.h"

std::vector <PhysicObject*> Physics::m_physicObjects;

void Physics::Run()
{
   for (int i = 0; i < m_physicObjects.size(); ++i)
   {
		PhysicObject* obj1 = m_physicObjects[i];

      for (int j = 0; j < m_physicObjects.size(); ++j)
      {
			PhysicObject* obj2 = m_physicObjects[j];

          if (obj1 == obj2)
              continue;
          else
              ResolveCollision(obj1, obj2);
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

