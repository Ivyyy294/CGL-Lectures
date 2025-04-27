#pragma once
#include "ParticleCollision.h"
#include <glm/glm.hpp>
#include "objects/ForceGenerator.h"
#include "objects/PhysicObject.h"
#include <vector>

class Physics {
public:
    static void Run (float deltaTime);
    static void RunPhysicForSingleObject(PhysicObject* obj, float deltaTime);

	 static void AddPhysicObject (PhysicObject* obj);
	 static void RemovePhysicObject (PhysicObject* obj);
	
	 static void AddForceGenerator(ForceGenerator* obj);
	 static void RemoveForceGenerator(ForceGenerator* obj);

private:
	static std::vector <PhysicObject*> m_physicObjects;
	static std::vector <ForceGenerator*> m_forceGenerator;
   
	static void RunPhysicForObject(float deltaTime, PhysicObject* obj);
	static void RunCollisionsForObject(float deltaTime, PhysicObject* obj, int startIndex = 0);
};
