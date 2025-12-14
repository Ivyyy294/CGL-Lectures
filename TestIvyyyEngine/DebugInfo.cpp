#include "DebugInfo.h"
#include <IvyyyTime.h>
#include "IvyyyDebug.h"

void DebugInfo::Start ()
{
	fontmesh = gameObject->GetComponent<D2D1FontMesh> ().get ();
}

void DebugInfo::Update ()
{
	UpdateFps();

	if (fontmesh != nullptr)
		fontmesh->text = L"FPS: " + std::to_wstring (fps) + L"\nDeltaTIme: " + std::to_wstring (deltatime);
	//else
	//	Debug::Log("FPS: " + std::to_string(fps) + ", DeltaTIme: " + std::to_string(deltatime));
}

void DebugInfo::UpdateFps()
{
	deltatime = Time::DeltaTime ();

	if (timer <= 1.f)
	{
		timer += deltatime;
		tmpFps++;
	}
	else
	{
		timer = 0.f;
		fps = tmpFps;
		tmpFps = 0;
	}
}
