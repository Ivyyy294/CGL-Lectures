#pragma once

#include "scenes/BaseScene.h"
#include "objects/BouncingBall.h"

class AssignmentScene3 : public BaseScene {
public:

	AssignmentScene3();
	virtual void DrawGUI() override;

	virtual const char* GetName() override { return "Assignment3"; };

private:
	BouncingBall* m_bb = nullptr;
};
