#include "GlobalForceField.h"
#include "Physics.h"

GlobalForceField::GlobalForceField()
	: ForceField (9.81)
{
	SetStatic (true);
}

GlobalForceField::GlobalForceField(float force)
: ForceField (force)
{
}

void GlobalForceField::ResolveCollision (PhysicObject* obj)
{
	obj->ApplyForce (glm::vec2(0.0f, m_force * -1.0f * obj->GetMass()));
}

