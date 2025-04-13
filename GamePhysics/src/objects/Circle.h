#pragma once
#include <glm/glm.hpp>
#include <imgui.h>

#include "objects//GameObject.h"
#include "objects/PhysicObject.h"

class Circle : public GameObject
{
public:
	Circle(glm::vec2 pos, float radius);

	void Draw() override;
	virtual void Update(float deltaTime) override {};

   inline const float& Radius() const { return m_circleRadius; }

protected:
	float m_circleRadius;
	ImColor m_color = ImColor (255, 255, 255, 255);
};
