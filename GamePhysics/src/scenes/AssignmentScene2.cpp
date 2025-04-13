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
	const float gravity = 0.981f;

	const float particleRadius = 0.1;
	const int particleCount = 10;

	gameObjects.push_back (new Wall (glm::vec2(-xMax, yMax), glm::vec2(xMax, yMax)));
	gameObjects.push_back (new Wall (glm::vec2(xMax, yMax), glm::vec2(xMax, -yMax)));
	gameObjects.push_back (new Wall (glm::vec2(xMax, -yMax), glm::vec2(-xMax, -yMax)));
	gameObjects.push_back (new Wall (glm::vec2(-xMax, -yMax), glm::vec2(-xMax, yMax)));

	for (int i = 0; i < particleCount; ++i)
		gameObjects.push_back(new BouncingBall(glm::vec2(0, 0), particleRadius));

	//Planet 1
	gameObjects.push_back (new CircleForceField (glm::vec2(-xMax * 0.5, -yMax * 0.5), gravityRadius, gravity));
	gameObjects.push_back(new BouncingBall(glm::vec2(-xMax * 0.5, -yMax * 0.5), planetRadius, true));

	//Planet 2
	gameObjects.push_back(new CircleForceField(glm::vec2(xMax * 0.5, -yMax * 0.5), gravityRadius, gravity));
	gameObjects.push_back(new BouncingBall(glm::vec2(xMax * 0.5, -yMax * 0.5), planetRadius, true));

	//Planet 3
	gameObjects.push_back(new CircleForceField(glm::vec2(0.0, yMax * 0.5), gravityRadius, gravity));
	gameObjects.push_back(new BouncingBall(glm::vec2(0.0, yMax * 0.5), planetRadius, true));
}

void AssignmentScene2::DrawGUI() {
    ImGui::Begin("Inspector");
    //ImGui::DragFloat2("Circle Position", &circlePosition[0], 0.1f);
    ImGui::End();
}
