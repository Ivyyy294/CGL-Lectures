#pragma once
#include <glm/glm.hpp>

class PhysicObject {
    friend class Physics;
public:
    PhysicObject(){};
    ~PhysicObject(){};

    inline const glm::vec2& Velocity() const { return m_velocity; }
    void ApplyForce(glm::vec2 force);
    inline bool IsStatic() const { return m_static; }
    inline void SetStatic (bool staitc) { m_static = staitc; }

protected:
   glm::vec2 m_velocity = glm::vec2 (0,0);
	bool m_static = false;
};
