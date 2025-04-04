#include "AssignmentScene1.h"
#include "objects//Physics.h"
#include "imgui.h"

AssignmentScene1::AssignmentScene1()
{
	//gameObjects.push_back (new Wall (glm::vec2(-maxX, maxY), glm::vec2(maxX, maxY)));
	//gameObjects.push_back (new Wall (glm::vec2(-maxX, -maxY), glm::vec2(maxX, -maxY)));
	//gameObjects.push_back (new Wall (glm::vec2(-maxX, maxY), glm::vec2(-maxX, -maxY)));
	//gameObjects.push_back (new Wall (glm::vec2(maxX, maxY), glm::vec2(maxX, -maxY)));

	gameObjects.push_back (new Wall (glm::vec2(-5, 0), glm::vec2(0, 5)));
	gameObjects.push_back (new Wall (glm::vec2(0, 5), glm::vec2(5, 0)));
	gameObjects.push_back (new Wall (glm::vec2(5, 0), glm::vec2(0, -5)));
	gameObjects.push_back (new Wall (glm::vec2(0, -5), glm::vec2(-5, 0)));


	gameObjects.push_back(new Circle (glm::vec2(1,1), 0.5f));
	gameObjects.push_back(new Circle (glm::vec2(-1,1), 0.5f));
	gameObjects.push_back(new Circle (glm::vec2(1,-1), 0.5f));
	gameObjects.push_back(new Circle (glm::vec2(-1,-1), 0.5f));

	Circle* centerCIrcle = new Circle(glm::vec2(0, 0), 0.75f);
   centerCIrcle->SetStatic(true);
	
	gameObjects.push_back(centerCIrcle);
}

void AssignmentScene1::OnEnable() {}

void AssignmentScene1::OnDisable() {}

void AssignmentScene1::Update(float deltaTime)
{
	for (size_t i = 0; i < gameObjects.size(); ++i) {
        gameObjects[i]->Update(deltaTime);
    }

	Physics::Run(gameObjects);
}

void AssignmentScene1::Draw()
{   
	for (size_t i = 0; i < gameObjects.size(); ++i) {
        gameObjects[i]->Draw();
    }
}

void AssignmentScene1::DrawGUI() {
    ImGui::Begin("Inspector");
    //ImGui::DragFloat2("Circle Position", &circlePosition[0], 0.1f);
    ImGui::End();
}
