#include "AssignmentScene1.h"

#include "imgui.h"

AssignmentScene1::AssignmentScene1()
    :
      topLeft(-4, 4),
      bottomRight(4, -4) 
{
}

void AssignmentScene1::OnEnable() {}

void AssignmentScene1::OnDisable() {}

void AssignmentScene1::Update(float deltaTime) {

	for (int i = 0; i < circleCount; ++i) {
        circles[i].Update(deltaTime, topLeft, bottomRight);
    }
}

void AssignmentScene1::Draw() {   

    DrawWalls();
    for (int i = 0; i < circleCount; ++i) {
        circles[i].Draw();
    }
}

void AssignmentScene1::DrawGUI() {
    ImGui::Begin("Inspector");
    //ImGui::DragFloat2("Circle Position", &circlePosition[0], 0.1f);
    ImGui::End();
}

void AssignmentScene1::DrawWalls() 
{
    Draw::Line(topLeft, glm::vec2(bottomRight.x, topLeft.y));
    Draw::Line(glm::vec2(topLeft.x, bottomRight.y), bottomRight);

	  Draw::Line(topLeft, glm::vec2(topLeft.x, bottomRight.y));
    Draw::Line(glm::vec2(bottomRight.x, topLeft.y), bottomRight);
}
