#pragma once

#include "core/Simple2DScene.h"
#include "objects/Particle.h"


class AssignmentScene1 : public Simple2DScene {
public:

	AssignmentScene1();
    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Assignment1"; };

private:
    int circleCount = 2;
    Particle circles[2] = {
		 Particle(glm::vec2(-1, 2), 1),
       Particle(glm::vec2(1, 2), 1)
	 };
    
    glm::vec2 topLeft;
    glm::vec2 bottomRight;

	 void DrawWalls();
};
