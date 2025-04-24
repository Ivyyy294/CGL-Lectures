#pragma once
#include "Collision.h"
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
   
	static void RunPhysicForObject(float deltaTime, PhysicObject* obj);
	static void RunCollisionsForObject(float deltaTime, PhysicObject* obj, int startIndex = 0);
	static void ResolveCollision(PhysicObject* obj1, PhysicObject* obj2, const Collision& collison);
	static void PushObjects (PhysicObject* obj1, PhysicObject* obj2, const Collision& collison);
	static void DeflectObjects (PhysicObject* obj1, PhysicObject* obj2, const Collision& collison);
	static void DeflectObjectStatic (PhysicObject* obj, glm::vec2 normal);
};
