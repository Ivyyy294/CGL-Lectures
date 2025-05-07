#pragma once
#include "BaseScene.h"

class PoolScene
	: public BaseScene
{
	public:
		PoolScene();
		virtual const char* GetName() override { return "Assignment5"; };
		virtual void Draw() override;
		virtual void DrawGUI() override;
		virtual void Update(float deltaTime) override;
	private:
		void SpawnTable(float width, float height);
		void SpawnBall(float width, float height);
		void SpawnScene();
		void Reset();
};