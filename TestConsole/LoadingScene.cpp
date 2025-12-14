#include "LoadingScene.h"
#include "PrefabLogo.h"
#include "Drawings.h"
#include "LoadingText.h"
#include "IvyyyScreen.h"

void LoadingScene::Init ()
{
	float xCenter = Screen::CurrentResolution().width * 0.5f;

	auto img = AddGameObject <PrefabLogo>();
	img->SetDrawing (Drawings::LoadingScreen ());
	Vector3 newPos = img->transform.GetLocalPosition();
	newPos.y += 14.f;
	img->transform.SetLocalPosition (newPos);

	auto text = AddGameObject <GameObject> ();
	text->AddComponent <D2D1FontMesh> ();
	text->AddComponent <LoadingText> ();
	text->transform.SetLocalPosition (Vector3(xCenter, 500.f, 0.f));
}
