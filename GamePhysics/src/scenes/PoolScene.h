#pragma once
#include "BaseScene.h"

class PoolScene
	: public BaseScene
{
	public:
		PoolScene();
		virtual const char* GetName() override { return "Pool Scene"; };
		virtual void Draw() override;

	private:
		void SpawnTable(float width, float height);
		void SpawnBall(float width, float height);
};