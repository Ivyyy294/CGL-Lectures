#include "ThrowBall.h"
#include <core/Input.h>
#include <core/Draw.h>
#include <imgui.h>
#include "BouncingBall.h"
#include "Physics.h"

ThrowBall::ThrowBall(BouncingBall* ball)
	: m_ball (ball)
{
}

void ThrowBall::Draw()
{
	if (m_isAiming)
	{
		Draw::SetColor (ImColor (255, 0, 0, 255));
		Draw::Arrow (m_spawnPos, m_targetPos);
		DrawTryjectory();
	}
}

void ThrowBall::DrawTryjectory()
{
	float maxPreviweTime = 2.0f;

	glm::vec2 impulse = GetImpulse();

	BouncingBall dummy (m_spawnPos, m_ball->Radius(), m_ball->GetMass());
	dummy.SetMass (m_ball->GetMass());

	dummy.ApplyImpulse (impulse);

	for ( float i = 0; i < maxPreviweTime; i += m_stepSize)
	{
		dummy.Update(m_stepSize);
		Physics::RunForPhysicObject (&dummy, m_stepSize);
		dummy.Draw();
	}
}

void ThrowBall::Update(float deltaTime)
{
	m_stepSize = deltaTime;

	if (Input::IsMouseClicked(ImGuiMouseButton_Left))
	{
		m_spawnPos = Input::GetMousePos();

		if (Draw::IsPointVisible (m_spawnPos))
		{
			m_targetPos = m_spawnPos;
			m_isAiming = true;
			m_ball->SetStatic (true);
			m_ball->SetTrigger (true);
			m_ball->SetPosition (m_spawnPos);
		}
	}
	else if (m_isAiming && Input::IsMouseDown(ImGuiMouseButton_Left))
		m_targetPos = Input::GetMousePos();
	else if (m_isAiming && Input::IsMouseReleased(ImGuiMouseButton_Left))
	{
		m_isAiming = false;
		ShootBall();
	}
}

void ThrowBall::ShootBall()
{
	m_ball->SetStatic(false);
	m_ball->SetTrigger(false);
	m_ball->SetVelocity (glm::vec2(0.0, 0.0));
	m_ball->ApplyImpulse (GetImpulse());
}

glm::vec2 ThrowBall::GetImpulse()
{
	return (m_targetPos - m_spawnPos);
}
