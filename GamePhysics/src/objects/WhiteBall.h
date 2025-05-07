#pragma once
#include "BouncingBall.h"

class WhiteBall
	: public BouncingBall
{
public:
	WhiteBall (glm::vec2 pos, float radius);
	~WhiteBall(){};

	void Update(float deltaTime) override;
	void Draw() override;

	void OnTriggerEnter(PhysicObject* obj) override;

private:
	bool m_isAiming = false;
	const glm::vec2 m_spawnPos;

	void ResetPosition();
	glm::vec2 GetImpulse();
};
