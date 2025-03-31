#pragma once
#include "IvyyyComponent.h"

#define IVYYY_D3D

class PlayerMovement
	: public Ivyyy::Component
{
public:
	void Update () override;

private:
	//float speed{ 1.f };
	float speed{ 256.f };
};

