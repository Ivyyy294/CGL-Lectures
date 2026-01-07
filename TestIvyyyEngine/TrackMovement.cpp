#include "TrackMovement.h"
#include "IvyyyDraw.h"
#include "IvyyyInput.h"
#include "IvyyyTime.h"
#include "IvyyyPhysicObject.h"
#include "IvyyyCamera.h"

void TrackMovement::Update()
{
	if (m_maxLength <= 0)
		return;

	float dist = transform->GetPosition().Distance(m_pos.back());

	if (dist > m_spacing)
	{
		m_pos.push_back (transform->GetPosition());
		
		if (m_pos.size() > m_maxLength)
			m_pos.erase (m_pos.begin());
	}

	for (int i = 1; i < m_pos.size(); i++)
		Draw::AddLine(m_pos[i-1], m_pos[i], m_color);

	Draw::AddLine(m_pos[m_pos.size() -1], transform->GetPosition(), m_color);
}

void TrackMovement::Start()
{
	m_pos.push_back (transform->GetLocalPosition());
}

