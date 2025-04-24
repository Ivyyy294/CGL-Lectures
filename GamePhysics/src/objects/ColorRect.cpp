#include "ColorRect.h"
#include <core/Draw.h>

ColorRect::ColorRect(glm::vec2 pos, float width, float height, ImColor color)
	: m_width (width)
	, m_height (height)
	, m_color (color)
{
	m_position = pos;
}

void ColorRect::Draw()
{
	Draw::SetColor (m_color);
	Draw::Rect (m_position, 0.0f, {m_width * 0.5f, m_height * 0.5f}, true);
}
