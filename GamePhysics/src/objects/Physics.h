#pragma once

#include "BouncingBall.h"
#include "Wall.h"
#include <glm/glm.hpp>

class Physics {
public:
    static void Run();
	 static void RunForPhysicObject(PhysicObject* obj, int startIndex = 0);
    static void ResolveCollision(PhysicObject* obj1, PhysicObject* obj2);

	 static void AddPhysicObject (PhysicObject* obj);
	 static void RemovePhysicObject (PhysicObject* obj);
	
	static float m_deltaTime;
private:
	static std::vector <PhysicObject*> m_physicObjects;
};
