#include "AssignmentScene4.h"
#include "imgui.h"
#include "objects/GlobalForceField.h"
#include "objects/Wall.h"
#include "objects/ThrowBall.h"
#include "objects/CircleForceField.h"

AssignmentScene4::AssignmentScene4()
{
	gameObjects.push_back (new GlobalForceField());

	m_bb = new BouncingBall(glm::vec2(0, 0), 0.5, 1.0f);
	m_bb->SetMass(1.0f);

	gameObjects.push_back(m_bb);
	
	gameObjects.push_back (new ThrowBall(m_bb));

	const int xMax = 8;
	const int yMax = 5;

	//cage
	gameObjects.push_back(new Wall(glm::vec2(-xMax, yMax), glm::vec2(xMax, yMax)));
	gameObjects.push_back(new Wall(glm::vec2(xMax, yMax), glm::vec2(xMax, -yMax)));
	gameObjects.push_back(new Wall(glm::vec2(xMax, -yMax), glm::vec2(-xMax, -yMax)));
	gameObjects.push_back(new Wall(glm::vec2(-xMax, -yMax), glm::vec2(-xMax, yMax)));

	//Lines
	gameObjects.push_back(new Wall(glm::vec2(-1.75f, -0.75f), glm::vec2(-1.0f, 0.0f)));
	gameObjects.push_back(new Wall(glm::vec2(-1.0f, 0.0f), glm::vec2(1.0f, 0.0f)));
	gameObjects.push_back(new Wall(glm::vec2(1.0f, 0.0f), glm::vec2(1.75f, -0.75f)));
}

void AssignmentScene4::DrawGUI() {
    ImGui::Begin("Inspector");
	 float mass = m_bb->GetMass();
    ImGui::DragFloat("Ball mass", &mass, 0.1f, 1.0f, 10.f);
	 m_bb->SetMass(mass);
    ImGui::End();
}
