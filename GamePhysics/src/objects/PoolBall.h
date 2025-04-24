#pragma
#include "BouncingBall.h"

class PoolBall
	: public BouncingBall
{
public:
	PoolBall (float radius, ImColor color);
	~PoolBall(){};

	void Draw() override;
private:

};
