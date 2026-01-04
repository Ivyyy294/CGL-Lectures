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
		size_t m_maxLength = 100;
		float m_spacing = 0.15f;

	public:
		void SetMaxLength (size_t length) {m_maxLength = length;}
		void SetLineSpacing (float spacing){m_spacing = spacing;}
		void Update() override;
		void Start() override;
		void SetColor(const Color& color) {m_color = color;};

	private:
};

