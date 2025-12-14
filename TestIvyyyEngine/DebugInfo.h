#pragma once
#include <IvyyyComponent.h>
#include <IvyyyD2D1FontMesh.h>

using namespace Ivyyy;

class DebugInfo :
    public Component
{
public:
	virtual void Start () override;
	virtual void Update () override;

private:
	int tmpFps{ 0 };
	int fps{ 0 };
	float deltatime{ 0.f };
	float timer{ 0.f };

	int m_colliderCount{ 0 };
	int m_meshCount{ 0 };

	D2D1FontMesh* fontmesh {nullptr };

	void UpdateFps();
	//void UpdateColliderCount();
};

