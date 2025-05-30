#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "GameObject.h"

class PhysicObject 
	: public GameObject
{
    friend class Physics;
    friend class ParticleCollision;
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
	 inline float GetIMass() const {return m_static ? 0.0f : m_iMass;}
	 void SetMass(float mass);

	 inline bool IsTrigger() const { return m_trigger; }
	 inline void SetTrigger(bool val) { m_trigger = val; }

	 inline bool IsSimulation() const { return m_simulation; }
	 inline void SetSimulation(bool val) { m_simulation = val; }

	 void SetLinearDamping (const float val);
	 inline float GetLinearDamping() {return m_linearDamping;};

	 glm::vec2 Reflection (glm::vec2 direction, glm::vec2 normal);
	 glm::vec2 GetForce();
protected:
   glm::vec2 m_velocity = glm::vec2 (0,0);
   glm::vec2 m_impulse = glm::vec2 (0,0);
   glm::vec2 m_force = glm::vec2 (0,0);

	float m_linearDamping = 0.0f; // v *= 1 - damping * deltatime (Linear damping)

	bool m_static = false;
	bool m_trigger = false;
	bool m_simulation = false;

	virtual void OnTriggerEnter (PhysicObject* obj) {};
	virtual void OnCollisionEnter (PhysicObject* obj) {};

private:
	float m_mass = 1.0f;
	float m_iMass = 1.0f;
};
