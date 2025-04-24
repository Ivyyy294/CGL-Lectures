#pragma once
#include <glm/glm.hpp>
#include <imgui.h>

#include "objects//GameObject.h"
#include "CircleCollider.h"

class Circle
	: public CircleCollider
{
public:
	Circle(float radius);
	Circle(glm::vec2 pos, float radius);
	Circle(glm::vec2 pos, float radius, ImColor color, bool trigger);

	void Draw() override;
	virtual void Update(float deltaTime) override {};

protected:
	ImColor m_color = ImColor (255, 255, 255, 255);
	bool m_fill = false;
};
