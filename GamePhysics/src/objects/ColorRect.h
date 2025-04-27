#pragma once
#include <imgui.h>
#include "GameObject.h"

class ColorRect
: public GameObject
{
public:
	ColorRect(glm::vec2 pos, float width, float height, ImColor color);
	~ColorRect(){};

	void Draw() override;
private:
	ImColor m_color;
	float m_width;
	float m_height;
};
