#pragma
#include "BouncingBall.h"

class PoolBall
	: public BouncingBall
{
public:
	PoolBall (glm::vec2 pos, float radius, ImColor color);
	~PoolBall(){};

	void Draw() override;
private:

};
