#pragma once

#include "core/Simple2DScene.h"
#include "objects/Circle.h"
#include "objects/Wall.h"

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
	GameObject::Vec gameObjects;
};
