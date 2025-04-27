#include "PoolPocket.h"
#include "core/Draw.h"
#include "PoolBall.h"
#include "WhiteBall.h"
#include "PoolGameState.h"

PoolPocket::PoolPocket(glm::vec2 pos, float colliderRadius, float drawRadius, ImColor color)
	: Circle (pos, colliderRadius, color, true)
	, m_drawRadius (drawRadius)
{
}

void PoolPocket::Draw()
{
	Draw::SetColor(m_color);
	Draw::Circle(m_position, m_drawRadius, true);
}

void PoolPocket::OnTriggerEnter(PhysicObject* obj)
{
	if (PoolBall* ball = dynamic_cast<PoolBall*>(obj))
	{
		if (ball->Number() == "8")
			PoolGameState::gameOver = true;
		else
			ball->SetActive(false);
	}
	else if (WhiteBall* ball = dynamic_cast <WhiteBall*>(obj))
		ball->ResetPosition();
}
