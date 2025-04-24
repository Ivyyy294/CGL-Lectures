#pragma once
#include <glm/glm.hpp>
#include <imgui.h>
#include <vector>
#include "GameObject.h"
#include "objects/PhysicObject.h"

class Wall : public PhysicObject
{
public:
    typedef std::vector<Wall> Vec;

    Wall(glm::vec2 start, glm::vec2 end);
    Wall(glm::vec2 start, glm::vec2 end, ImColor color);

    void Draw() override;
    void Update(float deltaTime) override;

	 inline const glm::vec2& Start() const { return m_start; }
    inline const glm::vec2& End() const { return m_end; }

	 glm::vec2 GetPointAtTime(float t);
	 glm::vec2 GetDirection();
	 glm::vec2 GetNormal();
	 float Length();

	 Collision TestCollision(PhysicObject* collider) final;
private:
    glm::vec2 m_start;
    glm::vec2 m_end;
	 ImColor m_color;
};