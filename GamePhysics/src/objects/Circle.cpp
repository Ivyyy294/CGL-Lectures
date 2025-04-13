#include "Circle.h"
#include <core/Draw.h>

Circle::Circle(glm::vec2 pos, float radius) {
    m_position = pos;
    m_circleRadius = radius;
}

void Circle::Draw() {
	Draw::SetColor (m_color);
   Draw::Circle(m_position, m_circleRadius);
}

