#pragma once
#include "IvyyyComponent.h"
#include "IvyyyFontMesh.h"
#include "AnimatedText.h"

using namespace Ivyyy;

class LoadingText
	: public Component
{
public:
	void Start () override;
	void Update () override;
private:
	FontMesh* fontMesh;
	AnimatedText pressEnter;
	AnimatedText welcome;

	float timer{ 0.f };
	int percent{ 0 };
};

