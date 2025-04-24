#include "PoolBall.h"
#include "core/Draw.h"

PoolBall::PoolBall(float radius, ImColor color)
	 : BouncingBall (radius)
{
	m_color = color;
	m_linearDamping = 1.25f;
}

void PoolBall::Draw()
{
	Draw::SetColor(m_color);
	Draw::Circle(m_position, m_radius, true);
}
