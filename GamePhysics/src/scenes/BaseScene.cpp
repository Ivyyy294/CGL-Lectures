#include "BaseScene.h"
#include "objects/Physics.h"

void BaseScene::OnEnable()
{
	for (size_t i = 0; i < gameObjects.size(); ++i)
	{
		if (PhysicObject* obj = dynamic_cast<PhysicObject*> (gameObjects[i]))
			Physics::AddPhysicObject (obj);
	}
}

void BaseScene::OnDisable()
{
	for (size_t i = 0; i < gameObjects.size(); ++i)
	{
		if (PhysicObject* obj = dynamic_cast<PhysicObject*> (gameObjects[i]))
			Physics::RemovePhysicObject(obj);
	}
}

void BaseScene::Update(float deltaTime)
{
	Physics::m_deltaTime = deltaTime;

	for (size_t i = 0; i < gameObjects.size(); ++i) {
		gameObjects[i]->Update(deltaTime);
	}

	Physics::Run();
}

void BaseScene::Draw()
{
	for (size_t i = 0; i < gameObjects.size(); ++i) {
		gameObjects[i]->Draw();
	}
}
