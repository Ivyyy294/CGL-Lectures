#include <IvyyyScreen.h>
#include "GameScene.h"
#include "PrefabDrawing.h"
#include "PrefabButton.h"
#include "PrefabButtonController.h"
#include "Drawings.h"
#include "PageController.h"

void GameScene::Init ()
{
	//Add Page Controller
	auto pageController = AddGameObject <GameObject> ()->AddComponent<PageController>();

	//Add PrefabDrawing
	float xCenter = Screen::CurrentResolution ().width * 0.5f;
	auto drawing = AddGameObject <PrefabDrawing> ();

	Vector3 newPos = drawing->transform.GetLocalPosition();
	newPos.y = 100.f;
	drawing->transform.SetLocalPosition (newPos);
	pageController->prefabDrawing = drawing.get ();

	//Add Page Text
	auto pageTextObj = AddGameObject<GameObject> ();
	pageTextObj->transform.SetSpace (Transform::Space::SCREEN);
	float width = 800.f;
	pageTextObj->transform.SetLocalPosition (Vector3 (xCenter -width * 0.5f, 315.f, 0.f));

	auto textMesh = pageTextObj->AddComponent <D2D1FontMesh> ();
	textMesh->GetTransform ()->SetPivot (Transform::Pivot::TOPLEFT);
	textMesh->SetSize (800.f, 200.f);
	textMesh->font.family = L"Consolas";
	textMesh->font.height = 16;
	textMesh->font.alignment = D2D1Font::VERTICAL_CENTER | D2D1Font::HORIZONTAL_TOP;
	pageController->textMesh = textMesh.get();

	//Add PrefabButtonController
	auto buttonController = AddGameObject <PrefabButtonController> ();
	buttonController->transform.SetLocalPosition (Vector3 (xCenter, 400.f, 0.f));
	pageController->buttonController = buttonController->GetComponent <ButtonController>().get();

	auto backButton = AddGameObject <PrefabButton> ();
	backButton->SetText (L"[ back ]");
	backButton->SetEvent ("Back");
	buttonController->AddButton (backButton.get ());

	for (int i = 0; i <= 6; ++i)
	{
		auto button = AddGameObject <PrefabButton> ();
		button->SetText (L"[ Button ]");
		button->SetEvent ("Answer" + std::to_string(i+1));
		buttonController->AddButton (button.get());
	}
}
