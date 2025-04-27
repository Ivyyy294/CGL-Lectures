#pragma once
#include <glm/glm.hpp>
#include "PhysicObject.h"

class ParticleCollision
{
public:
	bool m_collision = false;
	glm::vec2 m_normal = glm::vec2(0.0f,  0.0f);
	float m_interrsectionDepth = 0.0f;
	float m_restitution = 1.0f;

	PhysicObject* obj1 = nullptr;
	PhysicObject* obj2 = nullptr;

	void Resolve();

private:
	void ResolveVelocity();
	void ResolveIntersection();
};