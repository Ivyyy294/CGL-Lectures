#include "PoolScene.h"
#include "objects/WhiteBall.h"
#include "objects/PoolBall.h"
#include "objects/ColorRect.h"
#include "objects/Circle.h"
#include <queue>

PoolScene::PoolScene()
{
	float width = 16.0f;
	float height = 8.0f;
	SpawnTable(width, height);
	SpawnBall(width, height);
}

void PoolScene::Draw()
{
	BaseScene::Draw();
}

void PoolScene::SpawnTable (float width, float height)
{
	float borderWidth = 0.75f;
	float pocketRadius = 0.4f;

	//Spawn borders
	gameObjects.push_back (new Wall ({width * -0.5f, height * 0.5f}, { width * 0.5f, height * 0.5f })); //top
	gameObjects.push_back(new Wall({ width * 0.5f, height * 0.5f }, { width * 0.5f, height * -0.5f })); //right
	gameObjects.push_back (new Wall ({width * -0.5f, height * -0.5f}, { width * 0.5f, height * -0.5f })); //bottom
	gameObjects.push_back(new Wall({ width * -0.5f, height * 0.5f }, { width * -0.5f, height * -0.5f })); //left

	gameObjects.push_back(new ColorRect ({0.0f, 0.0f}, width, height, ImColor (21, 88, 67, 255)));

	//Deco border
	gameObjects.push_back(new ColorRect ({0.0f, (height + borderWidth) * 0.5f }, width + borderWidth * 2.0f, borderWidth, ImColor (37, 140, 75, 255)));
	gameObjects.push_back(new ColorRect ({0.0f, (height + borderWidth) * -0.5f }, width + borderWidth * 2.0f, borderWidth, ImColor (37, 140, 75, 255)));
	
	gameObjects.push_back(new ColorRect ({(width + borderWidth) * -0.5f, 0.0f}, borderWidth, height + borderWidth * 2.0f, ImColor (37, 140, 75, 255)));
	gameObjects.push_back(new ColorRect ({(width + borderWidth) * 0.5f, 0.0f}, borderWidth, height + borderWidth * 2.0f, ImColor (37, 140, 75, 255)));

	//Deco Pockets
	gameObjects.push_back (new Circle ({0.0f, (height + pocketRadius) * 0.5f}, pocketRadius, {0.0f, 0.0f, 0.0f, 1.0f}, true));
	gameObjects.push_back(new Circle({ (width) * -0.5, (height) * 0.5f }, pocketRadius, { 0.0f, 0.0f, 0.0f, 1.0f }, true));
	gameObjects.push_back(new Circle({ (width) * 0.5, (height) * 0.5f }, pocketRadius, { 0.0f, 0.0f, 0.0f, 1.0f }, true));

	gameObjects.push_back (new Circle ({0.0f, (height + pocketRadius) * -0.5f}, pocketRadius, {0.0f, 0.0f, 0.0f, 1.0f}, true));
	gameObjects.push_back(new Circle({ (width) * -0.5, (height) * -0.5f }, pocketRadius, { 0.0f, 0.0f, 0.0f, 1.0f }, true));
	gameObjects.push_back(new Circle({ (width) * 0.5, (height) * -0.5f }, pocketRadius, { 0.0f, 0.0f, 0.0f, 1.0f }, true));

	//Draw white line
	gameObjects.push_back(new Wall({ width * 0.25f, height * 0.5f }, { width * 0.25f, height * -0.5f })); //right
	((Wall*)gameObjects.back())->SetTrigger (true);
}

void PoolScene::SpawnBall(float width, float height)
{
	float ballRadius = 0.3f;
	gameObjects.push_back(new WhiteBall({ width * 0.25f, 0.0f }, ballRadius));

	std::queue <PoolBall*> ballQueue;

	ballQueue.push (new PoolBall {{0.0f, 0.0f}, ballRadius, {1.0f, 1.0f, 0.0f, 1.0f}, "1", false}); //Yellow 1
	ballQueue.push (new PoolBall {{0.0f, 0.0f}, ballRadius, {1.0f, 0.0f, 0.0f, 1.0f}, "11", true}); //Red 11
	ballQueue.push (new PoolBall {{0.0f, 0.0f}, ballRadius, {1.0f, 0.275f, 0.0f, 1.0f}, "5", false}); //Orange 5
	ballQueue.push (new PoolBall {{0.0f, 0.0f}, ballRadius, {0.0f, 0.0f, 1.0f, 1.0f}, "2", false}); //Blue 2
	ballQueue.push (new PoolBall {{0.0f, 0.0f}, ballRadius, {0.0f, 0.0f, 0.0f, 1.0f}, "8", false}); //Black 8
	ballQueue.push (new PoolBall {{0.0f, 0.0f}, ballRadius, {0.0f, 0.0f, 1.0f, 1.0f}, "10", true}); //Blue 10
	ballQueue.push (new PoolBall {{0.0f, 0.0f}, ballRadius, {1.0f, 1.0f, 0.0f, 1.0f}, "9", true}); //Yellow 9
	ballQueue.push (new PoolBall {{0.0f, 0.0f}, ballRadius, {0.5f, 0.0f, 0.0f, 1.0f}, "7", false}); //Dark Red 7
	ballQueue.push (new PoolBall {{0.0f, 0.0f}, ballRadius, {0.0f, 1.0f, 0.0f, 1.0f}, "14", true}); //green 14
	ballQueue.push (new PoolBall {{0.0f, 0.0f}, ballRadius, {1.0f, 0.0f, 1.0f, 1.0f}, "4", false}); //pruple 4
	ballQueue.push (new PoolBall {{0.0f, 0.0f}, ballRadius, {0.0f, 1.0f, 0.0f, 1.0f}, "6", false}); //green 6
	ballQueue.push (new PoolBall {{0.0f, 0.0f}, ballRadius, {0.5f, 0.0f, 0.0f, 1.0f}, "15", true}); //Dark Red 15
	ballQueue.push (new PoolBall {{0.0f, 0.0f}, ballRadius, {1.0f, 0.275f, 0.0f, 1.0f}, "13", true}); //Orange 13
	ballQueue.push (new PoolBall {{0.0f, 0.0f}, ballRadius, {1.0f, 0.0f, 0.0f, 1.0f}, "3", false}); //Red 3
	ballQueue.push (new PoolBall {{0.0f, 0.0f}, ballRadius, {1.0f, 0.0f, 1.0f, 1.0f}, "12", false}); //pruple 12

	for (int i = 0; i < 5; ++i)
	{
		float xPos = (width * -0.15f) + (-ballRadius * 2.0f * i);

		for (int j = 0; j <= i; ++j)
		{
			float yPos = (ballRadius * i) - (ballRadius * 2.0f * j);

			PoolBall* ball = ballQueue.front();
			ballQueue.pop();
			ball->SetPosition ({ xPos, yPos });

			gameObjects.push_back(ball);
		}
	}
}
