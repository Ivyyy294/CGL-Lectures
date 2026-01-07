#include "ReferenceFrame.h"
#include <IvyyyDraw.h>

void ReferenceFrame::Draw()
{
	DrawAxis (m_position, m_up, Color::Green);
	DrawAxis (m_position, m_right, Color::Red);
	DrawAxis (m_position, m_forward, Color::Blue);
}

void ReferenceFrame::DrawAxis(const Vector3& pos, const Vector3& direction, const Color& color)
{
	Vector3 endPos = pos + direction;
	Draw::AddLine (pos, endPos, color);
	Draw::AddCircle (endPos * 0.8f, endPos.Normalized(), endPos.Magnitude() * 0.075f, 8, color);
	Draw::AddCircle (endPos * 0.85f, endPos.Normalized(), endPos.Magnitude() * 0.06f, 8, color);
	Draw::AddCircle (endPos * 0.9f, endPos.Normalized(), endPos.Magnitude() * 0.045f, 8, color);
	Draw::AddCircle (endPos * 0.95f, endPos.Normalized(), endPos.Magnitude() * 0.03f, 8, color);
}

ReferenceFrame& ReferenceFrame::operator*= (const float rhs)
{
	m_up *= rhs;
	m_right *= rhs;
	m_forward *= rhs;

	return *this;
}