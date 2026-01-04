#pragma once
#include "IvyyyScene.h"
#include "IvyyyColor.h"

using namespace Ivyyy;

class KeplerOrbitScene :
    public Scene
{
	private:
		void Init() override;
		void GridTest();

		GameObject* AddPlanet (float mass, bool isStatic, float size, Vector3 position
			, Vector3 velocity, Color color, int trackLength);
	};

