#pragma once
#include "Planet.h"
#include "PhysicObject.h"

class PlanetGravity
	: public PhysicObject
{
public:
	PlanetGravity(Planet* planet);
	~PlanetGravity(){};

	static float m_universalGravitationalConstant;

private:
	Planet* m_planet;

	void Update(float deltaTime) override;

	Collision TestCollision(PhysicObject* collider) final;
	void OnTriggerEnter(PhysicObject* obj, const Collision& collision) final;
};
