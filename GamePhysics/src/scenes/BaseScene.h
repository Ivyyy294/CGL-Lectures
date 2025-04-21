#pragma once

#include "core/Simple2DScene.h"
#include "objects/Circle.h"
#include "objects/Wall.h"

class BaseScene : public Simple2DScene {
public:
	BaseScene(){};
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void DrawGUI() override{};

protected:
	GameObject::Vec gameObjects;

	void ClearScene();
};