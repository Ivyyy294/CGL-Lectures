#include "Score.h"
#include "IvyyyEventSystem.h"

void Score::Start ()
{
	fontMesh = gameObject->GetComponent <D2D1FontMesh> ();
	EventSystem::Me ()->Event ("coin").Bind <Score, &Score::OnCoinCollected> (this);
}

void Score::Update ()
{
	fontMesh.lock()->text = L"Score: " + std::to_wstring (score);
}

void Score::Exit ()
{
	EventSystem::Me ()->Event ("coin").Release (this);
}

void Score::OnCoinCollected ()
{
	score++;
}
