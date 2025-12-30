#pragma once
#include "IvyyyScene.h"
#include "IvyyyMeshMaterial.h"

using namespace Ivyyy;

class SpaceCoonScene : public Ivyyy::Scene
{
	// Inherited via Scene
	void Init() override;
	void SpawnPlayer();
	void SpawnAsteroid();
	void SpawnAsteroid(float size, float mass, MeshMaterial::Ptr material);
	void SpawnColliders();
	void SpawnUi();
};

