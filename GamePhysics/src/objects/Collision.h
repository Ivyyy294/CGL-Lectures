#pragma once
#include <glm/glm.hpp>

struct Collision
{
	bool m_collision = false;
	glm::vec2 m_normal = glm::vec2(0.0f,  0.0f);
	float m_interrsectionDepth = 0.0f;
};