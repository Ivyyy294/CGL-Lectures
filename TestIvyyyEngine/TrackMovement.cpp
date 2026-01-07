#include "TrackMovement.h"
#include "IvyyyDraw.h"
#include "IvyyyInput.h"
#include "IvyyyTime.h"
#include "IvyyyPhysicObject.h"
#include "IvyyyCamera.h"

void TrackMovement::LateUpdate()
{
	if (m_maxLength <= 0)
		return;

	float dist = m_pos.size() == 0 ? m_spacing : transform->GetPosition().Distance(m_pos.back());

	if (dist >= m_spacing)
	{
		m_pos.push_back (transform->GetPosition());
		
		if (m_pos.size() > m_maxLength)
			m_pos.erase (m_pos.begin());
	}

	if (m_pos.size() < 2)
		return;

	for (size_t i = 1; i < m_pos.size(); i++)
		Draw::AddLine(m_pos[i-1], m_pos[i], m_color);

	Draw::AddLine(m_pos[m_pos.size() -1], transform->GetPosition(), m_color);
}


