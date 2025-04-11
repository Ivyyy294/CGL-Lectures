#pragma once

#include "scenes/BaseScene.h"
#include "objects/BouncingBall.h"
#include "objects/Wall.h"

class AssignmentScene1 : public BaseScene {
public:

	AssignmentScene1();
	virtual void DrawGUI() override;

	virtual const char* GetName() override { return "Assignment1"; };
};
