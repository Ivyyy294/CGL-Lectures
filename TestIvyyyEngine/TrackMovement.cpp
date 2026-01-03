#include "TrackMovement.h"
#include "IvyyyDraw.h"

void TrackMovement::Update()
{
	Draw::AddLine(Vector3::Back * 2.f, Vector3::Forward, Color::Green);
	Draw::AddLine(Vector3::Back * 10.f, Vector3::Forward * 10.f, Color::Green);
}
