#pragma once
#include "IvyyyComponent.h"
#include "IvyyyColor.h"

using namespace Ivyyy;

class TrackMovement :
    public Component
{
	private:
		std::vector<Vector3> m_pos;
		Color m_color = Color::White;

	public:
		void Update() override;
		void Start() override;
		void SetColor(const Color& color) {m_color = color;};

	private:
};

