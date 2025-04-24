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

		//Prevent collision with self in case startIndex was not passed
		if (startIndex == 0 && obj == obj2)
			continue;

		if ((obj->IsTrigger() && obj2->IsTrigger())
		|| (obj->IsStatic() && obj2->IsStatic()))
			continue;

		Collision collision1 = obj->TestCollision (obj2);

		if (collision1.m_collision)
		{
			ResolveCollision (obj, obj2, collision1);
			continue;
		}

		Collision collision2 = obj2->TestCollision (obj);
		if (collision2.m_collision)
			ResolveCollision(obj2, obj, collision2);
	}
}

void Physics::ResolveCollision(PhysicObject* obj1, PhysicObject* obj2, const Collision& collison)
{
	if (obj1->IsTrigger() || obj2->IsTrigger())
	{
		obj1->OnTriggerEnter(obj2, collison);
		obj2->OnTriggerEnter(obj1, collison);
		return;
	}

	obj1->OnCollisionEnter(obj2, collison);
	obj2->OnCollisionEnter(obj1, collison);

	DeflectObjects (obj1, obj2, collison);

	//distance
	PushObjects (obj1, obj2, collison);
}

void Physics::PushObjects(PhysicObject* obj1, PhysicObject* obj2, const Collision& collison)
{
	float distance1 = obj1->IsStatic() ? 0.0f : collison.m_interrsectionDepth * (obj2->IsStatic() ? 1.0f : 0.5f);
	float distance2 = obj2->IsStatic() ? 0.0f : collison.m_interrsectionDepth * (obj1->IsStatic() ? 1.0f : 0.5f);

	if (!obj2->IsSimulation())
		obj1->m_position += collison.m_normal * distance1;

	if (!obj1->IsSimulation())
		obj2->m_position += -collison.m_normal * distance2;
}

void Physics::DeflectObjects(PhysicObject* obj1, PhysicObject* obj2, const Collision& collison)
{
	glm::vec2 normal1 = collison.m_normal;
	glm::vec2 normal2 = -collison.m_normal;

	//glm::vec2 vDiff1 = collison.m_normal;
	//glm::vec2 vDiff2 = -collison.m_normal;

	//glm::vec2 force1On2 = normal1 * glm::dot(normal1, force1);
	//glm::vec2 force2On1 = normal2 * glm::dot(normal2, force2);

	//if (!obj2->IsSimulation())
	//	obj1->ApplyImpulse(-force1);

	//if (!obj1->IsSimulation())
	//	obj2->ApplyImpulse(-force2);

	////glm::vec2 force1On2 = force1 - force2;
	////glm::vec2 force2On1 = force2 - force1;

	//if (!obj2->IsSimulation())
	//{
	//	obj1->ApplyImpulse(-force1On2);
	//	obj1->ApplyImpulse(force2On1);
	//}

	//if (!obj1->IsSimulation())
	//{
	//	obj2->ApplyImpulse(-force2On1);
	//	obj2->ApplyImpulse(force1On2);
	//}

	//New

	glm::vec2 force1 = dot(normal1, obj1->GetForce()) * normal1;
	glm::vec2 force2 = dot(normal2, obj2->GetForce()) * normal2;

	//Old
	glm::vec2 deflect1 {0.0f, 0.0f}; //Impulse from obj2 on obj1
	glm::vec2 deflect2 {0.0f, 0.0f}; //Impulse from obj1 on obj2

	//Reflect
	deflect1 = obj1->m_velocity - 2.0f * glm::dot(obj1->m_velocity, normal1) * normal1;
	deflect2 = obj2->m_velocity - 2.0f * glm::dot(obj2->m_velocity, normal2) * normal2;

	if (!obj2->IsSimulation())
	{
		obj1->SetVelocity (deflect1 / obj1->m_mass);
		obj1->ApplyImpulse (force2);
	}

	if (!obj1->IsSimulation())
	{
		obj2->SetVelocity (deflect2 / obj2->m_mass);
		obj2->ApplyImpulse (force1);
	}
}

void Physics::DeflectObjectStatic(PhysicObject* obj, glm::vec2 normal)
{
	glm::vec2 newVelocity = obj->m_velocity - 2.0f * glm::dot(obj->m_velocity, normal) * normal;
	obj->m_velocity = glm::vec2(0.0f, 0.0f);
	obj->ApplyImpulse(newVelocity);
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


