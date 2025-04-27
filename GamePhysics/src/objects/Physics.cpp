#include "Physics.h"
#include "ParticleCollisionDetector.h"

std::vector <PhysicObject*> Physics::m_physicObjects;
std::vector <ForceGenerator*> Physics::m_forceGenerator;

void Physics::Run(float deltaTime)
{
   for (int i = 0; i < m_physicObjects.size(); ++i)
		RunPhysicForObject(deltaTime, m_physicObjects[i]);

	for (int i = 0; i < m_physicObjects.size(); ++i)
		RunCollisionsForObject(deltaTime, m_physicObjects[i], i + 1);
}

void Physics::RunPhysicForObject(float deltaTime, PhysicObject* obj)
{
	if (obj->IsStatic() || !obj->IsActive())
		return;
	
	for (size_t i = 0; i < m_forceGenerator.size(); i++)
		m_forceGenerator[i]->ApplyForceForObject(obj);

	//apply damping
	obj->m_velocity *= 1 - obj->m_linearDamping * deltaTime;

	glm::vec2 zero = glm::vec2(0.0f, 0.0f);

	obj->m_velocity += obj->m_impulse + obj->m_force * deltaTime;

	obj->m_impulse = zero;
	obj->m_force = zero;

	obj->m_position += obj->m_velocity * deltaTime;
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

		if (!obj->IsActive() || !obj2->IsActive())
			continue;

		//Prevent collision with self in case startIndex was not passed
		if (startIndex == 0 && obj == obj2)
			continue;

		if ((obj->IsTrigger() && obj2->IsTrigger())
		|| (obj->IsStatic() && obj2->IsStatic()))
			continue;

		ParticleCollision collision1 = ParticleCollisionDetector::TestCollision (obj, obj2);

		if (collision1.m_collision)
		{
			collision1.Resolve();
			continue;
		}

		ParticleCollision collision2 = ParticleCollisionDetector::TestCollision(obj2, obj);
		if (collision2.m_collision)
			collision2.Resolve();
	}
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

void Physics::AddForceGenerator(ForceGenerator* obj)
{
	m_forceGenerator.push_back (obj);
}

void Physics::RemoveForceGenerator(ForceGenerator* obj)
{
	for (auto i = m_forceGenerator.begin(); i != m_forceGenerator.end(); i++)
	{
		if (*i == obj)
		{
			m_forceGenerator.erase(i);
			return;
		}
	}
}


