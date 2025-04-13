#include "GlobalForceField.h"
#include "Physics.h"

GlobalForceField::GlobalForceField()
{
	SetStatic (true);
}

GlobalForceField::GlobalForceField(float force)
: m_force (force)
{
}

void GlobalForceField::Update(float deltaTime)
{
}

void GlobalForceField::ResolveCollision(PhysicObject* obj)
{
	obj->ApplyForce (glm::vec2 (0.0f, (m_force * std::pow(Physics::m_deltaTime, 2)) * -1.0f));
}

