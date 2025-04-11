#pragma once
#include <glm/glm.hpp>

#include "objects//GameObject.h"
#include "objects/PhysicObject.h"

class Circle : public GameObject
{
public:
	Circle(glm::vec2 pos, float radius);

	void Draw() override;
	virtual void Update(float deltaTime) override {};

	inline const glm::vec2& Position() const {return circlePosition;}
   inline const float& Radius() const { return circleRadius; }

protected:
	glm::vec2 circlePosition;
	float circleRadius;
};
