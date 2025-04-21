#pragma once
#include <glm/glm.hpp>
#include <vector>

class PhysicObject {
    friend class Physics;
public:
    PhysicObject();
    ~PhysicObject();

    inline const glm::vec2& Velocity() const { return m_velocity; }

	 void ApplyImpulse (glm::vec2 force);
	 void ApplyForce (glm::vec2 force);

	 inline void SetVelocity(glm::vec2 velocity) {m_velocity = velocity;};

    inline bool IsStatic() const { return m_static; }
    inline void SetStatic (bool val) { m_static = val; }

	 inline float GetMass() const {return m_mass;}
	 inline void SetMass(float mass) {m_mass = mass;}

	 inline bool IsTrigger() const { return m_trigger; }
	 inline void SetTrigger(bool val) { m_trigger = val; }

	 virtual void OnTriggerEnter (PhysicObject*){};

	 glm::vec2 Reflection (glm::vec2 direction, glm::vec2 normal);
protected:
	float m_mass = 1.0f;
   glm::vec2 m_velocity = glm::vec2 (0,0);
   glm::vec2 m_impulse = glm::vec2 (0,0);
   glm::vec2 m_force = glm::vec2 (0,0);

	bool m_static = false;
	bool m_trigger = false;

	virtual void ResolveCollision (PhysicObject* obj) = 0;
};
