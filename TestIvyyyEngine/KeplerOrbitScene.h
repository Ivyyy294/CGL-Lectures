#pragma once
#include "IvyyyScene.h"
#include "IvyyyColor.h"
#include "PlanetData.h"
#include "IvyyyPhysicObject.h"
#include "SolarObject.h"

using namespace Ivyyy;

class KeplerOrbitScene :
    public Scene
{
	private:
		void Init() override;
		void SpawnSolarObjects (SolarObject& root);
	};

