#include "GlobalForceField.h"
#include "Physics.h"

GlobalForceField::GlobalForceField()
	: ForceGenerator (9.81)
{
}

GlobalForceField::GlobalForceField(float force)
: ForceGenerator (force)
{
}

void GlobalForceField::ApplyForceForObject(PhysicObject* obj)
{
	obj->ApplyForce (glm::vec2(0.0f, m_appliedForce * -1.0f * obj->GetMass()));
}

