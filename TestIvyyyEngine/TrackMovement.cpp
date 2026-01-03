#include "TrackMovement.h"
#include "IvyyyDraw.h"
#include "IvyyyInput.h"
#include "IvyyyTime.h"
#include "IvyyyPhysicObject.h"

void TrackMovement::Update()
{
	float dist = transform->GetPosition().Distance(m_pos.back());

	if (dist > 0.1f)
	{
		m_pos.push_back (transform->GetPosition());
		
		if (m_pos.size() > 150)
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

