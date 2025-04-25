#include "PoolBall.h"
#include "core/Draw.h"

PoolBall::PoolBall(glm::vec2 pos, float radius, ImColor color, const std::string& number, bool halfFilled)
	 : BouncingBall (radius)
	 , m_number (number)
	 , m_halfFilled (halfFilled)
{
	m_position = pos;
	m_color = color;
	m_linearDamping = 1.25f;
}

void PoolBall::Draw()
{
	if (m_halfFilled)
	{
		Draw::SetColor({1.0f, 1.0f, 1.0f, 1.0f});
		Draw::Circle(m_position, m_radius, true);
		Draw::SetColor(m_color);

		//x sind
		//y cos
		int stepCount = 8;
		float stepSize = 0.75f / stepCount;
		for (int i = 0; i < stepCount; i++)
		{
			float y = sin (stepSize * i);
			float x = cos (stepSize * i);
			Draw::Rect(m_position, 0.0f, {x * m_radius, y * m_radius}, true);
		}
	}
	else
	{
		Draw::SetColor(m_color);
		Draw::Circle(m_position, m_radius, true);
	}

	Draw::SetColor({1.0f, 1.0f, 1.f, 1.0f});
	Draw::Circle(m_position, m_radius / 1.75f, true);
	Draw::SetColor({0.0f, 0.0f, 0.f, 1.0f});
	glm::vec2 textPos = m_position + glm::vec2{-m_radius * 0.2f * m_number.length(), m_radius * 0.5f};
	Draw::Text (textPos, m_number.c_str());
}
