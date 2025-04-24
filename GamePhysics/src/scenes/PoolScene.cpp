#include "PoolScene.h"
#include "objects/WhiteBall.h"
#include "objects/PoolBall.h"
#include "objects/ColorRect.h"
#include "objects/Circle.h"

PoolScene::PoolScene()
{
	float width = 16.0f;
	float height = 8.0f;
	SpawnTable(width, height);
	SpawnBall(width, height);
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

	for (int i = 0; i < 5; ++i)
	{
		float xPos = (width * -0.15f) + (-ballRadius * 2.0f * i);

		for (int j = 0; j <= i; ++j)
		{
			float yPos = (-ballRadius * i) + (ballRadius * 2.0f * j);
			gameObjects.push_back(new PoolBall({ xPos, yPos }, ballRadius, ImColor(1.0f, 0.0f, 0.0f, 1.0f)));
		}
	}
}
