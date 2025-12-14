#pragma once
#include <IvyyyGameObject.h>
#include <IvyyyD2D1FontMesh.h>

using namespace Ivyyy;

class PrefabDrawing :
    public GameObject
{
public:
	PrefabDrawing ();
	void SetDrawing (const std::wstring& drawing);

protected:
	D2D1FontMesh* fontMesh;
};

