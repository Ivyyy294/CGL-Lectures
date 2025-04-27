#include "BaseScene.h"
#include "objects/Physics.h"

void BaseScene::OnEnable()
{
	for (size_t i = 0; i < gameObjects.size(); ++i)
	{
		if (PhysicObject* obj = dynamic_cast<PhysicObject*> (gameObjects[i]))
			Physics::AddPhysicObject (obj);
		if (ForceGenerator* obj = dynamic_cast<ForceGenerator*> (gameObjects[i]))
			Physics::AddForceGenerator(obj);
	}
}

void BaseScene::OnDisable()
{
	for (size_t i = 0; i < gameObjects.size(); ++i)
	{
		if (PhysicObject* obj = dynamic_cast<PhysicObject*> (gameObjects[i]))
			Physics::RemovePhysicObject(obj);
		if (ForceGenerator* obj = dynamic_cast<ForceGenerator*> (gameObjects[i]))
			Physics::RemoveForceGenerator(obj);
	}
}

void BaseScene::Update(float deltaTime)
{
	for (size_t i = 0; i < gameObjects.size(); ++i)
	{
		if (gameObjects[i]->IsActive())
			gameObjects[i]->Update(deltaTime);
	}

	Physics::Run(deltaTime);
}

void BaseScene::Draw()
{
	for (size_t i = 0; i < gameObjects.size(); ++i)
	{
		if (gameObjects[i]->IsActive())
		{
			gameObjects[i]->Draw();
			Draw::Reset();
		}
	}
}

void BaseScene::ClearScene()
{
	OnDisable();

	for (size_t i = 0; i < gameObjects.size(); i++)
		delete (gameObjects[i]);

	gameObjects.clear();
}
