#include "PhysicObject.h"

void PhysicObject::ApplyForce(glm::vec2 force)
{
    // V3
     float length = glm::length(m_velocity);
     m_velocity += force;
     m_velocity = glm::normalize(m_velocity) * length;

   //V2
    //float length = glm::length(m_velocity);
    //m_velocity = glm::normalize(force) * length;

   //V1
    //if (std::abs (force.x) >= std::abs (force.y))
    //    m_velocity.x *= -1.f;
    //else if (std::abs(force.y) >= std::abs(force.x))
    //    m_velocity.y *= -1.f;
}