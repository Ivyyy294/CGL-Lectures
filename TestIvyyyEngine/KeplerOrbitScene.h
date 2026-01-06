#pragma once
#include "IvyyyScene.h"
#include "IvyyyColor.h"
#include "PlanetData.h"
#include "IvyyyPhysicObject.h"

using namespace Ivyyy;

class KeplerOrbitScene :
    public Scene
{
	private:
		void Init() override;

		GameObject* AddPlanet (float mass, bool isStatic, float size, Vector3 position
			, Vector3 velocity, Color color, int trackLength, float lineSpacing);

		GameObject* AddPlanet(const PlanetData& data, const PhysicObject* soi);
	};

