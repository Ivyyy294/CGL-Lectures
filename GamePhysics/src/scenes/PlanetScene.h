#pragma once

#include "scenes/BaseScene.h"
#include "objects/Circle.h"
#include "objects/Wall.h"

class PlanetScene : public BaseScene {
public:

	PlanetScene();

	virtual const char* GetName() override { return "PlanetScene"; };
	virtual void DrawGUI() override;
private:
	float m_sunDistance = 3.3f;
	float m_sunMass = 105.0f;
	float m_planetMass = 1.1f;
	glm::vec2 m_planetVelocity = glm::vec2 (0.0f, -3.0f);

	void Restart();
	void SpawnPlanets();
};
