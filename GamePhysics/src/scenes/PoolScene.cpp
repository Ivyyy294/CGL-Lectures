#include "PoolScene.h"
#include "objects/WhiteBall.h"
#include "objects/PoolBall.h"

PoolScene::PoolScene()
{
	gameObjects.push_back(new WhiteBall(0.5f));
	gameObjects.push_back(new PoolBall(0.5f, ImColor (1.0f, 0.0f, 0.0f, 1.0f)));
}
