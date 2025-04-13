#pragma once

#include "scenes/BaseScene.h"
#include "objects/Circle.h"
#include "objects/Wall.h"

class AssignmentScene2 : public BaseScene {
public:

	AssignmentScene2();

	virtual const char* GetName() override { return "Assignment2"; };

private:
	void SpawnPlanet (float xpos, float ypos, float gravRadius, float planetRadius, float gravity);
};
