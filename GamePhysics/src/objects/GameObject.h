#pragma once
#include <vector>

class  GameObject {
public:
	typedef std::vector<GameObject*> Vec;

    GameObject(){};
    ~GameObject(){};

	 virtual void Draw() = 0;
    virtual void Update(float deltaTime) = 0;
};
