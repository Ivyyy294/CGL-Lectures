#pragma once

#include <glm/glm.hpp>

#include "core/Simple2DScene.h"

class TestScene : public Simple2DScene {
public:
    TestScene();
    ~TestScene();

    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Test Scene"; }

private:
    glm::vec2 circlePosition;
    float circleRadius;
};