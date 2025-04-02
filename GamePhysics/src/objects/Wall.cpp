#include "core//Draw.h"
#include "Wall.h"

Wall::Wall(glm::vec2 start, glm::vec2 end) 
: m_start (start)
, m_end (end)
{
    m_static = true;
}

void Wall::Draw()
{
    Draw::Line(m_start, m_end);
}

void Wall::Update(float deltaTime) {}

glm::vec2 Wall::GetPointAtTime(float t) {
    if (t < 0)
        return m_start;
    else if (t > 1)
        return m_end;
	 else
	 {
        float x = m_start.x + t * (m_end.x - m_start.x);
        float y = m_start.y + t * (m_end.y - m_start.y);
        return glm::vec2(x,y);
    }
}

