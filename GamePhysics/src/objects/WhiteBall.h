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
private:
	bool m_isAiming = false;
};
