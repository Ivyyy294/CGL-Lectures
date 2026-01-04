#include "PlanetRings.h"
#include "IvyyyDraw.h"

void PlanetRings::Update()
{
	for (size_t i = 0; i < m_rings.size(); ++i)
		Draw::AddCircle (transform->GetPosition(), transform->GetRotation() * Vector3::Back
		, m_rings[i], 16 , m_color);
}
