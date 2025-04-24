#include "WhiteBall.h"
#include "core/Input.h"
#include "core/Draw.h"
#include "Physics.h"

WhiteBall::WhiteBall (float radius)
	: BouncingBall (radius)
{
	m_color = ImColor (1.0f, 1.0f, 1.0f, 1.0f);
	m_linearDamping = 1.25f;
}

void WhiteBall::Update(float deltaTime)
{
	if (Input::IsMouseClicked(ImGuiMouseButton_Left))
	{
		m_velocity = glm::vec2(0.0f, 0.0f);
		m_isAiming = true;
		SetStatic (true);
	}
	else if (m_isAiming && Input::IsMouseReleased(ImGuiMouseButton_Left))
	{
		m_isAiming = false;
		SetStatic (false);
		ApplyImpulse (Input::GetMousePos() - m_position);
	}
}

void WhiteBall::Draw()
{
	Draw::SetColor(m_color);
	Draw::Circle(m_position, m_radius, true);

	if (m_isAiming)
	{
		glm::vec2 mousePos = Input::GetMousePos();

		Draw::SetColor(ImColor(255, 0, 0, 255));
		Draw::Arrow(m_position, mousePos);

		float maxPreviweTime = 2.0f;

		glm::vec2 impulse = mousePos - m_position;

		BouncingBall dummy(m_position, m_radius, m_mass);
		dummy.SetSimulation(true);
		dummy.SetLinearDamping(m_linearDamping);
		dummy.ApplyImpulse(impulse);

		float stepSize = 1.0f / 24.0f;

		for (float i = 0; i < maxPreviweTime; i += stepSize)
		{
			dummy.Update(stepSize);
			Physics::RunPhysicForSingleObject(&dummy, stepSize);
			dummy.Draw();
		}
	}
}
