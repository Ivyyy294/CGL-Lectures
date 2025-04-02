#include "Circle.h"
#include <core/Draw.h>

Circle::Circle(glm::vec2 pos, float radius) {
    circlePosition = pos;
    circleRadius = radius;

	 float vX = rand() % 5 * 0.01f;
	 float vY = rand() % 5 * 0.01f;

    m_velocity = glm::vec2(vX, vY);
}

void Circle::Draw() {
   Draw::Circle(circlePosition, circleRadius);
    Draw::Line(circlePosition, glm::vec2(0, 0));
}

void Circle::Update(float deltaTime) {

   if (m_static)
        return;

	m_velocity.y -= 0.981f * std::pow(deltaTime, 2);
	circlePosition += m_velocity;

        //if (circlePosition.y - circleRadius <= bottomRight.y ||
        //    circlePosition.y + circleRadius > topLeft.y) {
        //    circleVelocity.y *= -1.f;
        //}

        //if (circlePosition.x - circleRadius <= topLeft.x ||
        //    circlePosition.x + circleRadius > bottomRight.x) {
        //    circleVelocity.x *= -1.f;
        //}
}

