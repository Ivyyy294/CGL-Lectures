#pragma once

#include "scenes/BaseScene.h"
#include "objects/Circle.h"
#include "objects/Wall.h"

class AssignmentScene2 : public BaseScene {
public:

	AssignmentScene2();
	virtual void DrawGUI() override;

	virtual const char* GetName() override { return "Assignment2"; };
};
