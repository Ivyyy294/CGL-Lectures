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
	//New
	float separatingVelocity = dot ((obj1->m_velocity - obj2->m_velocity), m_normal);

	// The contact is either separating or stationary - there’s
	// no impulse required.
	if (separatingVelocity > 0.0f)
		return;

	// Calculate the new separating velocity.
	float newSepVelocity = -separatingVelocity * m_restitution;
	float deltaVelocity = newSepVelocity - separatingVelocity;

	float iMass1 = obj1->GetIMass();
	float iMass2 = obj2->GetIMass();
	float totalInverseMass = iMass1 + iMass2;

	// If all particles have infinite mass, then impulses have no effect.
	if (totalInverseMass <= 0.0f) return;

	// Calculate the impulse to apply.
	float impulse = deltaVelocity / totalInverseMass;

	// Find the amount of impulse per unit of inverse mass.
	glm::vec2 impulsePerIMass = m_normal * impulse;

	if (!obj2->IsSimulation())
		obj1->SetVelocity(obj1->m_velocity + impulsePerIMass * iMass1);

	if (!obj1->IsSimulation())
		obj2->SetVelocity(obj2->m_velocity + impulsePerIMass * -iMass2);
}

void ParticleCollision::ResolveIntersection()
{
	if (m_interrsectionDepth <= 0.0f)
		return;

	float iMass1 = obj1->GetIMass();
	float iMass2 = obj2->GetIMass();
	float totalInverseMass = iMass1 + iMass2;

	// If all particles have infinite mass, then impulses have no effect.
	if (totalInverseMass <= 0.0f) return;

	glm::vec2 movePerIMass = m_normal * (m_interrsectionDepth / totalInverseMass);

	if (!obj2->IsSimulation())
		obj1->m_position += movePerIMass * iMass1;

	if (!obj1->IsSimulation())
		obj2->m_position += movePerIMass * -iMass2;
}
