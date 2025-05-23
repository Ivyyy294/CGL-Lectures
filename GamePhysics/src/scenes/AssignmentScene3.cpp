#include "AssignmentScene3.h"
#include "imgui.h"
#include "objects/GlobalForceField.h"
#include "objects/Wall.h"
#include "objects/ThrowBall.h"
#include "objects/CircleForceField.h"

AssignmentScene3::AssignmentScene3()
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

	//ball
	gameObjects.push_back (new CircleForceField (glm::vec2(xMax * 0.5, yMax * 0.5f), 3.0f, 20.0f));
}

void AssignmentScene3::DrawGUI() {
    ImGui::Begin("Inspector");
	 float mass = m_bb->GetMass();
    ImGui::DragFloat("Ball mass", &mass, 0.1f, 1.0f, 10.f);
	 m_bb->SetMass(mass);
    ImGui::End();
}
