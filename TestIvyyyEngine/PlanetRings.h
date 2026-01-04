#pragma once
#include "IvyyyComponent.h"
#include <vector>
#include "IvyyyColor.h"

using namespace Ivyyy;


class PlanetRings :
    public Component
{
	public:
		void SetColor (const Color& color) {m_color = color;}
		void SetRings (const std::vector<float>& rings) { m_rings = rings;}
	private:
		std::vector<float> m_rings;
		Color m_color;

		void Update() override;
};

