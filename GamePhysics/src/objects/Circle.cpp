#include "Circle.h"
#include <core/Draw.h>

Circle::Circle(glm::vec2 pos, float radius) {
    circlePosition = pos;
    circleRadius = radius;
}

void Circle::Draw() {
   Draw::Circle(circlePosition, circleRadius);
    Draw::Line(circlePosition, glm::vec2(0, 0));
}

