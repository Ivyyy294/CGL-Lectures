#include "BaseScene.h"
#include "objects/Physics.h"

void BaseScene::OnEnable()
{
	for (size_t i = 0; i < gameObjects.size(); ++i)
	{
		if (PhysicObject* obj = dynamic_cast<PhysicObject*> (gameObjects[i]))
			Physics::AddPhysicObject (obj);
		if (ForceField* obj = dynamic_cast<ForceField*> (gameObjects[i]))
			Physics::AddForceField(obj);
	}
}

void BaseScene::OnDisable()
{
	for (size_t i = 0; i < gameObjects.size(); ++i)
	{
		if (PhysicObject* obj = dynamic_cast<PhysicObject*> (gameObjects[i]))
			Physics::RemovePhysicObject(obj);
		if (ForceField* obj = dynamic_cast<ForceField*> (gameObjects[i]))
			Physics::RemoveForceField(obj);
	}
}

void BaseScene::Update(float deltaTime)
{
	for (size_t i = 0; i < gameObjects.size(); ++i)
		gameObjects[i]->Update(deltaTime);

	Physics::Run(deltaTime);
}

void BaseScene::Draw()
{
	for (size_t i = 0; i < gameObjects.size(); ++i)
		gameObjects[i]->Draw();
}
