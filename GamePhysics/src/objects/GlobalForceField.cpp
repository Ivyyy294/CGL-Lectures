#include "GlobalForceField.h"

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
	m_forceThisFrame.y = (0.981f * std::pow(deltaTime, 2)) * -1.0;
}

void GlobalForceField::ResolveCollision(PhysicObject* obj)
{
	obj->ApplyForce (m_forceThisFrame);
}
