#include "GlobalForceField.h"
#include "Physics.h"

GlobalForceField::GlobalForceField()
	: ForceField (9.81)
{
}

GlobalForceField::GlobalForceField(float force)
: ForceField (force)
{
}

glm::vec2 GlobalForceField::GetForceForObject(PhysicObject* obj)
{
	return glm::vec2 (0.0f, m_force * -1.0f * obj->GetMass());
}

