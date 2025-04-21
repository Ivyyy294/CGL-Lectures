#pragma once

#include "BouncingBall.h"
#include "Wall.h"
#include <glm/glm.hpp>
#include "objects/ForceField.h"
#include "objects/PhysicObject.h"
#include <vector>

class Physics {
public:
    static void Run (float deltaTime);
    static void RunPhysicForSingleObject(PhysicObject* obj, float deltaTime);

	 static void AddPhysicObject (PhysicObject* obj);
	 static void RemovePhysicObject (PhysicObject* obj);
	
	 static void AddForceField(ForceField* obj);
	 static void RemoveForceField(ForceField* obj);

private:
	static std::vector <PhysicObject*> m_physicObjects;
	static std::vector <ForceField*> m_forceFields;
   
	static void ResolveCollision(PhysicObject* obj1, PhysicObject* obj2);
	static void RunPhysicForObject(float deltaTime, PhysicObject* obj);
	static void RunCollisionsForObject(float deltaTime, PhysicObject* obj, int startIndex = 0);
};
