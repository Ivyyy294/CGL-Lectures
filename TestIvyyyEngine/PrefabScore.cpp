#include "PrefabScore.h"
#include "Score.h"
#include "IvyyyD2D1FontMesh.h"

PrefabScore::PrefabScore ()
{
	AddComponent<D2D1FontMesh> ();
	AddComponent<Score> ();
	transform.SetSpace (Transform::Space::SCREEN);
	transform.SetPivot (Transform::Pivot::TOPLEFT);
}
