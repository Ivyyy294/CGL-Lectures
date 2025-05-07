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
	float m_sunDistance = 5.0f;
	float m_sunMass = 105.0f;
	glm::vec2 m_sunVelocity = glm::vec2(0.0f, 3.5f);

	float m_planetMass = 0.5f;
	glm::vec2 m_planetOffset = glm::vec2 (-5.5f, 0.0f);
	glm::vec2 m_planetVelocity = glm::vec2 (0.0f, -5.5f);

	void Restart();
	void SpawnPlanets();
};
