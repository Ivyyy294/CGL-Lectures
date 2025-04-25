#pragma once
#include "Circle.h"

class PoolPocket
	: public Circle
{
public:
	PoolPocket(glm::vec2 pos, float colliderRadius, float drawRadius, ImColor color);
	~PoolPocket(){};

	void Draw() override;
	void OnTriggerEnter(PhysicObject* obj, const Collision& collision) override;

private:
	float m_drawRadius;
};
