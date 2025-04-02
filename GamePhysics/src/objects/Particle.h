#pragma once
#include <glm/glm.hpp>

class Particle {
public:

	Particle(glm::vec2 pos, float radius);

    glm::vec2 circlePosition;
    float circleRadius;
    glm::vec2 circleVelocity;


	 void Draw();
    void Update(float deltaTime, glm::vec2 topLeft, glm::vec2 bottomRight);
};
