#pragma once
#include <vector>
#include <glm/glm.hpp>

class  GameObject {
	friend class Physics;
public:
	typedef std::vector<GameObject*> Vec;

    GameObject(){};
    ~GameObject(){};

	 virtual void Draw() = 0;
    virtual void Update(float deltaTime) = 0;

	 inline void SetPosition (const glm::vec2& pos) { m_position = pos;}
	 inline const glm::vec2& GetPosition () const { return m_position;}

protected:
	glm::vec2 m_position = glm::vec2(0.0, 0.0);
};
