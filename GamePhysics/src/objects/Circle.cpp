#include "Circle.h"
#include <core/Draw.h>

Circle::Circle(glm::vec2 pos, float radius) {
    m_circlePosition = pos;
    m_circleRadius = radius;
}

void Circle::Draw() {
	Draw::SetColor (m_color);
   Draw::Circle(m_circlePosition, m_circleRadius);
}

