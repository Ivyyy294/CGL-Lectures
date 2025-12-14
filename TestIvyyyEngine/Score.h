#pragma once
#include <IvyyyComponent.h>
#include <IvyyyD2D1FontMesh.h>
#include <memory>

using namespace Ivyyy;

class Score :
    public Component
{
public:
		virtual void Start () override;
		virtual void Update () override;
		virtual void Exit () override;

		void OnCoinCollected ();
private:
	int score{ 0 };

	std::weak_ptr <D2D1FontMesh> fontMesh;
};

