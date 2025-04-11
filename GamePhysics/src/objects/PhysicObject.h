#pragma once
#include <glm/glm.hpp>
#include <vector>

class PhysicObject {
    friend class Physics;
public:
    PhysicObject();
    ~PhysicObject();

    inline const glm::vec2& Velocity() const { return m_velocity; }

    void ApplyForce (glm::vec2 force);
	 void ApplyImpulse (glm::vec2 force);

    inline bool IsStatic() const { return m_static; }
    inline void SetStatic (bool val) { m_static = val; }

	 //inline bool IsTrigger() const { return m_static; }
	 //inline void SetTrigger(bool val) { m_trigger = val; }

	 virtual void OnTriggerEnter (PhysicObject*){};

protected:
   glm::vec2 m_velocity = glm::vec2 (0,0);
	bool m_static = false;
	//bool m_trigger = false;

	virtual void ResolveCollision (PhysicObject* obj) = 0;
};
