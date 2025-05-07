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
