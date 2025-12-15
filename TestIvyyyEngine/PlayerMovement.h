#pragma once
#include "IvyyyRenderer.h"
#include "IvyyyComponent.h"
#include "IvyyyTransform.h"

using namespace Ivyyy;

class PlayerMovement
	: public Ivyyy::Component
{
public:
	void Start() override;
	void Update () override;
	//void FixedUpdate () override;

	void OnMouseDown() override;
private:
	Vector3 moveVec;
	float speed{2.f};
};

