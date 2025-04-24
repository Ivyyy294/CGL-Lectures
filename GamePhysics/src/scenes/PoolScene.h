#pragma once
#include "BaseScene.h"

class PoolScene
	: public BaseScene
{
	public:
		PoolScene();
		virtual const char* GetName() override { return "Pool Scene"; };
};