#include "Particle.h"
#include <core/Draw.h>

Particle::Particle(glm::vec2 pos, float radius) {
    circlePosition = pos;
    circleRadius = radius;
    circleVelocity = glm::vec2(0, 0);
}

void Particle::Draw() {
   Draw::Circle(circlePosition, circleRadius);
    Draw::Line(circlePosition, glm::vec2(0, 0));
}

void Particle::Update(float deltaTime, glm::vec2 topLeft, glm::vec2 bottomRight) {
        circleVelocity.y -= 0.981f * std::pow(deltaTime, 2);
        circlePosition += circleVelocity;

        if (circlePosition.y - circleRadius <= bottomRight.y ||
            circlePosition.y + circleRadius > topLeft.y) {
            circleVelocity.y *= -1.f;
        }

        if (circlePosition.x - circleRadius <= topLeft.x ||
            circlePosition.x + circleRadius > bottomRight.x) {
            circleVelocity.x *= -1.f;
        }
}
