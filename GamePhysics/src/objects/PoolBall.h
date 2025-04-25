#pragma
#include "BouncingBall.h"
#include <string>

class PoolBall
	: public BouncingBall
{
public:
	PoolBall (glm::vec2 pos, float radius, ImColor color, const std::string& number, bool halfFilled);
	~PoolBall(){};

	void Draw() override;
private:
	const std::string m_number;
	bool m_halfFilled;
};
