#pragma once
#include "IvyyyScene.h"

using namespace Ivyyy;

class SpaceCoonScene : public Ivyyy::Scene
{
	// Inherited via Scene
	void Init() override;
	void SpawnPlayer();
	void SpawnAsteroid();
	void SpawnAsteroid(float size, float mass);
	void SpawnColliders();
};

