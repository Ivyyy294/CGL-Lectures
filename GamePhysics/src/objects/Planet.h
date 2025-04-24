#pragma once
#include "Circle.h"
#include <imgui.h>

class Planet
: public Circle
{
public:
	Planet (float radius, float mass, ImColor color = ImColor (1.0f, 1.0f, 1.0f, 1.0f));
	~Planet(){};

	static float m_ScaleOneTo;

private:

	void Draw() override;
	void Update(float deltaTime) override{};

	float GetScale();
};
