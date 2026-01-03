#pragma once
#include "IvyyyScene.h"

using namespace Ivyyy;

class KeplerOrbitScene :
    public Scene
{
	// Inherited via Scene
	void Init() override;
	void GridTest();
};

