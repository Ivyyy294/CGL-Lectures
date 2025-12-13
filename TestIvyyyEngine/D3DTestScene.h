#pragma once
#include "IvyyyScene.h"

using namespace Ivyyy;

class D3DTestScene : public Scene
{
protected:
	virtual void Init() override;

private:
	void InitColorCubes();
	void InitTextureCubes();
};

