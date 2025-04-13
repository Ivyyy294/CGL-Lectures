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
		Draw::Line (m_spawnPos, m_targetPos);
		DrawTryjectory();
	}
}

void ThrowBall::DrawTryjectory()
{
	const float deltaTime = Physics::m_deltaTime;
	float stepSize = 1.0f / 30.0f;
	float maxPreviweTime = 1.0f;

	Physics::m_deltaTime = stepSize;
	glm::vec2 impulse = GetImpulse();
	BouncingBall dummy (m_spawnPos, m_ball->Radius());

	dummy.ApplyImpulse (impulse);
	float force = glm::length (impulse);

	for ( float i = 0; i < maxPreviweTime; i += stepSize)
	{
		dummy.Update(stepSize);
		Physics::RunForPhysicObject (&dummy);
		//m_ball->ApplyForce (Physics::GetForceForPhysicObject(m_ball, stepSize));
		dummy.Draw();
	}

	Physics::m_deltaTime = deltaTime;
}

void ThrowBall::Update(float deltaTime)
{
	if (Input::IsMouseClicked(ImGuiMouseButton_Left))
	{
		m_spawnPos = Input::GetMousePos();

		if (Draw::IsPointVisible (m_spawnPos))
		{
			m_targetPos = m_spawnPos;
			m_isAiming = true;
			m_ball->SetStatic (true);
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
	m_ball->ApplyImpulse (GetImpulse());
}

glm::vec2 ThrowBall::GetImpulse()
{
	return (m_targetPos - m_spawnPos) * 0.1f;
}
