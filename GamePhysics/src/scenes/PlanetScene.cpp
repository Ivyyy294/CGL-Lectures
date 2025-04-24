#include "PlanetScene.h"
#include "objects//Physics.h"
#include "imgui.h"
#include "objects/Planet.h"
#include "objects/PlanetGravity.h"

PlanetScene::PlanetScene()
{
	PlanetGravity::m_universalGravitationalConstant = 1.0f;
	Planet::m_ScaleOneTo = 1.0f;

	SpawnPlanets();
}

void PlanetScene::DrawGUI()
{
	ImGui::Begin("Inspector");

	ImGui::SeparatorText("Universal values");

	ImGui::DragFloat("Gravitational Constant", &PlanetGravity::m_universalGravitationalConstant, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat("Scale", &Planet::m_ScaleOneTo, 0.1f);

	ImGui::SeparatorText("Initial values");

	ImGui::DragFloat("Sun mass", &m_sunMass, 1.0f, 0.001f);
	ImGui::DragFloat("Sun distance", &m_sunDistance, 0.1f, 0.0f, 10.0f);
	ImGui::DragFloat("Planet mass", &m_planetMass, 1.0f, 1.0f, 100.0f);
	ImGui::DragFloat2("Planet velocity", &m_planetVelocity[0], 0.1f);
	
	ImGui::Separator();

	if (ImGui::Button ("Reset"))
		Restart();

	ImGui::End();
}

void PlanetScene::Restart()
{
	ClearScene();
	SpawnPlanets();
	OnEnable();
}

void PlanetScene::SpawnPlanets()
{
	Planet* sun1 = new Planet(0.75f, m_sunMass, ImColor(255, 204, 51));
	sun1->SetPosition(glm::vec2(-m_sunDistance * 0.5f, 0.0f));
	sun1->SetVelocity(glm::vec2(0.0f, 4.0f));
	gameObjects.push_back(sun1);
	gameObjects.push_back (new PlanetGravity (sun1));

	Planet* sun2 = new Planet(0.75f, m_sunMass, ImColor(255, 204, 51));
	sun2->SetPosition(glm::vec2(m_sunDistance * 0.5f, 0.0f));
	sun2->SetVelocity(glm::vec2(0.0f, -4.0f));
	gameObjects.push_back(sun2);
	gameObjects.push_back (new PlanetGravity (sun2));

	Planet* earth = new Planet(0.3, m_planetMass, ImColor(107, 147, 214));
	earth->SetPosition(sun1->GetPosition() + glm::vec2(-2.0f, 0.0f));
	earth->SetVelocity(m_planetVelocity);
	gameObjects.push_back(earth);
	gameObjects.push_back (new PlanetGravity (earth));
}
