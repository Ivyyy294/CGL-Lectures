#include "PrefabCoin.h"
#include <IvyyyD2D1FontMesh.h>
#include <IvyyyRectCollider.h>
#include "Coin.h"

PrefabCoin::PrefabCoin ()
{
	D2D1FontMesh* fontMesh = AddComponent<D2D1FontMesh> ().get ();
	fontMesh->SetSize (100.f, 24.f);
	fontMesh->text = L"Coin";
	fontMesh->font.family = L"Consolas";
	fontMesh->font.height = 16;
	fontMesh->font.alignment = D2D1Font::HORIZONTAL_CENTER | D2D1Font::VERTICAL_CENTER;
	fontMesh->drawGizmo = true;

	if (auto collider = AddComponent <RectCollider> ())
	{
		collider->SetSize (fontMesh->GetWidth (), fontMesh->GetHeight ());
		collider->SetTrigger (true);
	}

	AddComponent <Coin> ();
}
