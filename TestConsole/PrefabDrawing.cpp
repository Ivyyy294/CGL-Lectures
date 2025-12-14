#include "PrefabDrawing.h"
#include "IvyyyScreen.h"
#include "Drawings.h"

PrefabDrawing::PrefabDrawing ()
{
	float width = 440.f;
	float height = 200.f;
	transform.SetSpace (Transform::Space::SCREEN);
	transform.SetPivot (Transform::Pivot::TOPLEFT);
	transform.SetLocalPosition (Vector3((Screen::CurrentResolution().width - width) * 0.5f, 0.f, 0.f));
	fontMesh = AddComponent<D2D1FontMesh> ().get();
	fontMesh->SetSize (width, height);
	fontMesh->text = L"Placeholder";
	fontMesh->font.family = L"Consolas";
	fontMesh->font.height = 16;
	fontMesh->font.color = Color (255, 255, 255);
	fontMesh->font.alignment = D2D1Font::VERTICAL_LEFT | D2D1Font::HORIZONTAL_TOP;
	//fontMesh->drawGizmo = true;
}

void PrefabDrawing::SetDrawing (const std::wstring& drawing)
{
	fontMesh->text = drawing;
}
