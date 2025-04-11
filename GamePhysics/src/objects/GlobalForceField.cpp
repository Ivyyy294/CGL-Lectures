#include "GlobalForceField.h"

GlobalForceField::GlobalForceField()
{
}

GlobalForceField::GlobalForceField(float force)
: m_force (force)
{
}

void GlobalForceField::Update(float deltaTime)
{
	m_deltaTime = deltaTime;
	m_forceThisFrame.y = (0.981f * std::pow(deltaTime, 2)) * -1.0;
}

void GlobalForceField::ResolveCollision(PhysicObject* obj)
{
	obj->ApplyForce (m_forceThisFrame);
}
