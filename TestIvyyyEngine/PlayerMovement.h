#pragma once
#include "IvyyyRenderer.h"
#include "IvyyyComponent.h"

class PlayerMovement
	: public Ivyyy::Component
{
public:
	void Update () override;

private:
	float speed{ Ivyyy::Renderer::GetMode() == Ivyyy::Renderer::Mode::DX11 ?  2.f : 256.f};
};

