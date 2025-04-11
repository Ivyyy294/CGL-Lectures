#include "Physics.h"
#include "GlobalForceField.h"

void Physics::Run()
{
   for (int i = 0; i < PhysicObject::m_physicObjects.size(); ++i)
   {
		PhysicObject* obj1 = PhysicObject::m_physicObjects[i];

      for (int j = 0; j < PhysicObject::m_physicObjects.size(); ++j)
      {
			PhysicObject* obj2 = PhysicObject::m_physicObjects[j];

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

