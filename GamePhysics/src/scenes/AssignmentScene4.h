#pragma once

#include "scenes/BaseScene.h"
#include "objects/BouncingBall.h"

class AssignmentScene4 : public BaseScene {
public:

	AssignmentScene4();
	virtual void DrawGUI() override;

	virtual const char* GetName() override { return "Assignment4"; };

private:
	BouncingBall* m_bb = nullptr;
};
