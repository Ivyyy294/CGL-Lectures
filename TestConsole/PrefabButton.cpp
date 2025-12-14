#include <IvyyyRectCollider.h>
#include "PrefabButton.h"

PrefabButton::PrefabButton ()
{
	transform.SetSpace (Transform::Space::SCREEN);
	transform.SetPivot (Transform::Pivot::TOPLEFT);

	fontMesh = AddComponent<D2D1FontMesh> ().get();
	fontMesh->SetSize (100.f, 24.f);
	fontMesh->text = L"Button";
	fontMesh->font.family = L"Consolas";
	fontMesh->font.height = 16;
	fontMesh->font.alignment = D2D1Font::HORIZONTAL_CENTER | D2D1Font::VERTICAL_CENTER;
	fontMesh->drawGizmo = true;

	if (auto collider = AddComponent <RectCollider> ())
		collider->SetSize (fontMesh->GetWidth (), fontMesh->GetHeight ());

	script = AddComponent <AnswerButton> ().get();
}
