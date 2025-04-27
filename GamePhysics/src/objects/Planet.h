#pragma once
#include "Circle.h"
#include <imgui.h>
#include "ForceGenerator.h"

class Planet
	: public Circle
	, public ForceGenerator
{
public:
	Planet (float radius, float mass, ImColor color = ImColor (1.0f, 1.0f, 1.0f, 1.0f));
	~Planet(){};

	static float m_ScaleOneTo;
	static float m_universalGravitationalConstant;

	void ApplyForceForObject(PhysicObject* obj) final;
private:

	void Draw() override;
	void Update(float deltaTime) override{};

	float GetScale();
};
