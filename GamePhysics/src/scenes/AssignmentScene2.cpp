#include "AssignmentScene2.h"
#include "objects//Physics.h"
#include "imgui.h"
#include "objects/CircleForceField.h"

AssignmentScene2::AssignmentScene2()
{
	const int xMax = 8;
	const int yMax = 5;
	const int gravityRadius = 5;
	const float planetRadius = 0.25;
	const float gravity = 9.81f;

	const float particleRadius = 0.05;
	const int particleCount = 250;
	const float particleMass = 5.0f;
	const float particleBonuce = 0.0f;

	gameObjects.push_back (new Wall (glm::vec2(-xMax, yMax), glm::vec2(xMax, yMax)));
	gameObjects.push_back (new Wall (glm::vec2(xMax, yMax), glm::vec2(xMax, -yMax)));
	gameObjects.push_back (new Wall (glm::vec2(xMax, -yMax), glm::vec2(-xMax, -yMax)));
	gameObjects.push_back (new Wall (glm::vec2(-xMax, -yMax), glm::vec2(-xMax, yMax)));

	for (int i = 0; i < particleCount; ++i)
	{
		BouncingBall* ball = new BouncingBall(glm::vec2(0, 0), particleRadius, particleMass, particleBonuce);
		gameObjects.push_back(ball);
	}

	//Planet 1
	SpawnPlanet (-xMax * 0.5f, -yMax * 0.5f, gravityRadius, planetRadius, gravity);

	//Planet 2
	SpawnPlanet(xMax * 0.5f, -yMax * 0.5f, gravityRadius, planetRadius, gravity);

	//Planet 3
	SpawnPlanet(0.0f, yMax * 0.5f, gravityRadius, planetRadius, gravity);
}

void AssignmentScene2::DrawGUI() {
    ImGui::Begin("Inspector");
    //ImGui::DragFloat2("Circle Position", &circlePosition[0], 0.1f);
    ImGui::End();
}

void AssignmentScene2::SpawnPlanet(float xpos, float ypos, float gravRadius, float planetRadius, float gravity)
{
	glm::vec2 pos (xpos, ypos);
	gameObjects.push_back(new CircleForceField (pos, gravRadius, gravity));
	//gameObjects.push_back(new CircleForceField (pos, planetRadius * 1.75f, -gravity));
	gameObjects.push_back(new BouncingBall (pos, planetRadius, true));
}
