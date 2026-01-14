#pragma once
#include "IvyyyComponent.h"

using namespace Ivyyy;

class CameraMovement :
    public Component
{
	private:
		float m_timeScale = 1.f;

	public:
		void Update() override;
};

