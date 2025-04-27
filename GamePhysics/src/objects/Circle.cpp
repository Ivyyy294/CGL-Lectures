#include "Circle.h"
#include <core/Draw.h>

Circle::Circle(float radius)
	: CircleCollider(radius)
{
}

Circle::Circle(glm::vec2 pos, float radius)
	: CircleCollider (radius)
{
    m_position = pos;
}

Circle::Circle(glm::vec2 pos, float radius, ImColor color, bool trigger)
	: CircleCollider(radius)
{
	m_position = pos;
	m_color = color;
	m_trigger = trigger;
	m_fill = true;
}

void Circle::Draw() {
	Draw::SetColor (m_color);
   Draw::Circle(m_position, m_radius, m_fill);
}

