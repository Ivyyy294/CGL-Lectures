#pragma once
#include <IvyyyComponent.h>
#include "Score.h"

using namespace Ivyyy;

class Coin :
    public Component
{
public:
	virtual void OnTriggerEnter (GameObject* trigger) override;
	virtual void OnDisable() override;
	virtual void OnEnable() override;
};

