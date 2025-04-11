#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "GameObject.h"
#include "objects/PhysicObject.h"

class Wall : public GameObject, public PhysicObject
{
public:
    typedef std::vector<Wall> Vec;

    Wall(glm::vec2 start, glm::vec2 end);

    void Draw() override;
    void Update(float deltaTime) override;

	 inline const glm::vec2& Start() const { return m_start; }
    inline const glm::vec2& End() const { return m_end; }

	 glm::vec2 GetPointAtTime(float t);

private:
    glm::vec2 m_start;
    glm::vec2 m_end;

	 void ResolveCollision(PhysicObject* obj) override;
};