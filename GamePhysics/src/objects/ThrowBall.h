#pragma once
#include "GameObject.h"
#include <glm/glm.hpp>
#include "BouncingBall.h"

class ThrowBall
	: public GameObject
{
public:
	ThrowBall(BouncingBall* ball);
	~ThrowBall(){};

private:
	BouncingBall* m_ball = nullptr;
	bool m_isAiming = false;
	glm::vec2 m_spawnPos = glm::vec2 (0.0, 0.0);
	glm::vec2 m_targetPos = glm::vec2 (0.0, 0.0);
	
	// Inherited via GameObject
	void Draw() override;

	void DrawTryjectory();

	void Update(float deltaTime) override;

	void ShootBall ();

	glm::vec2 GetImpulse();

	float m_stepSize = 0.0f;
};
