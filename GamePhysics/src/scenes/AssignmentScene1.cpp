#include "AssignmentScene1.h"
#include "objects//Physics.h"
#include "imgui.h"
#include "objects//GlobalForceField.h"

AssignmentScene1::AssignmentScene1()
{
	gameObjects.push_back (new GlobalForceField ());
	//gameObjects.push_back (new Wall (glm::vec2(-maxX, maxY), glm::vec2(maxX, maxY)));
	//gameObjects.push_back (new Wall (glm::vec2(-maxX, -maxY), glm::vec2(maxX, -maxY)));
	//gameObjects.push_back (new Wall (glm::vec2(-maxX, maxY), glm::vec2(-maxX, -maxY)));
	//gameObjects.push_back (new Wall (glm::vec2(maxX, maxY), glm::vec2(maxX, -maxY)));

	gameObjects.push_back (new Wall (glm::vec2(-5, 0), glm::vec2(0, 5)));
	gameObjects.push_back (new Wall (glm::vec2(0, 5), glm::vec2(5, 0)));
	gameObjects.push_back (new Wall (glm::vec2(5, 0), glm::vec2(0, -5)));
	gameObjects.push_back (new Wall (glm::vec2(0, -5), glm::vec2(-5, 0)));

	gameObjects.push_back(new BouncingBall (glm::vec2(1,1), 0.5f));
	gameObjects.push_back(new BouncingBall(glm::vec2(-1,1), 0.5f));
	gameObjects.push_back(new BouncingBall(glm::vec2(1,-1), 0.5f));
	gameObjects.push_back(new BouncingBall(glm::vec2(-1,-1), 0.5f));

	gameObjects.push_back(new BouncingBall(glm::vec2(0, 0), 0.75f, true));
}

void AssignmentScene1::DrawGUI() {
    ImGui::Begin("Inspector");
    //ImGui::DragFloat2("Circle Position", &circlePosition[0], 0.1f);
    ImGui::End();
}
