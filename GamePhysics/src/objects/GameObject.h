#pragma once
#include <vector>
#include <glm/glm.hpp>

class  GameObject {
	friend class Physics;
	friend class ParticleCollision;
public:
	typedef std::vector<GameObject*> Vec;

    GameObject(){};
    ~GameObject(){};

	 virtual void Draw(){};
    virtual void Update(float deltaTime){};

	 inline void SetPosition (const glm::vec2& pos) { m_position = pos;}
	 inline const glm::vec2& GetPosition () const { return m_position;}

	 inline void SetActive(bool val) {m_active = val;}
	 inline bool IsActive() const {return m_active;}

protected:
	glm::vec2 m_position = glm::vec2(0.0, 0.0);
	bool m_active = true;
};
