#include "ParticleCollision.h"

void ParticleCollision::Resolve()
{
	if (obj1->IsTrigger() || obj2->IsTrigger())
	{
		obj1->OnTriggerEnter(obj2);
		obj2->OnTriggerEnter(obj1);
		return;
	}

	obj1->OnCollisionEnter(obj2);
	obj2->OnCollisionEnter(obj1);

	ResolveVelocity();
	ResolveIntersection();
}

void ParticleCollision::ResolveVelocity()
{
	glm::vec2 normal1 = m_normal;
	glm::vec2 normal2 = -m_normal;

	//New
	glm::vec2 relativeVelocity = obj1->m_velocity - obj2->m_velocity;

	glm::vec2 force1 = dot(normal1, obj1->GetForce()) * normal1;
	glm::vec2 force2 = dot(normal2, obj2->GetForce()) * normal2;

	//Old
	glm::vec2 deflect1{ 0.0f, 0.0f }; //Impulse from obj2 on obj1
	glm::vec2 deflect2{ 0.0f, 0.0f }; //Impulse from obj1 on obj2

	//Reflect
	deflect1 = obj1->m_velocity - 2.0f * glm::dot(obj1->m_velocity, normal1) * normal1;
	deflect2 = obj2->m_velocity - 2.0f * glm::dot(obj2->m_velocity, normal2) * normal2;

	if (!obj2->IsSimulation())
	{
		obj1->SetVelocity(deflect1 / obj1->m_mass);
		obj1->ApplyImpulse(force2);
	}

	if (!obj1->IsSimulation())
	{
		obj2->SetVelocity(deflect2 / obj2->m_mass);
		obj2->ApplyImpulse(force1);
	}
}

void ParticleCollision::ResolveIntersection()
{
	float distance1 = obj1->IsStatic() ? 0.0f : m_interrsectionDepth * (obj2->IsStatic() ? 1.0f : 0.5f);
	float distance2 = obj2->IsStatic() ? 0.0f : m_interrsectionDepth * (obj1->IsStatic() ? 1.0f : 0.5f);

	if (!obj2->IsSimulation())
		obj1->m_position += m_normal * distance1;

	if (!obj1->IsSimulation())
		obj2->m_position += -m_normal * distance2;
}
