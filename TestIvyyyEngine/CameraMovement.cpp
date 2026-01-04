#include "CameraMovement.h"
#include "IvyyyInput.h"
#include "IvyyyTime.h"
#include "IvyyyDraw.h"

void CameraMovement::Update()
{
	Quaternion currentRot = transform->GetRotation();
	Vector3 position = transform->GetPosition();
	Quaternion newRot = Quaternion::Identity;

	//Rotation
	if (Input::KeyPressed(Key::KEY_UP))
		newRot = newRot * Quaternion::Euler(currentRot * Vector3(-45.f * Time::DeltaTime(), 0.f, 0.f));

	if (Input::KeyPressed(Key::KEY_DOWN))
		newRot = newRot * Quaternion::Euler(currentRot * Vector3(45.f * Time::DeltaTime(), 0.f, 0.f));

	if (Input::KeyPressed(Key::KEY_RIGHT))
		newRot = newRot * Quaternion::Euler(currentRot * Vector3(0.f, 45.f * Time::DeltaTime(), 0.f));
	if (Input::KeyPressed(Key::KEY_LEFT))
		newRot = newRot * Quaternion::Euler(currentRot * Vector3(0.f, -45.f * Time::DeltaTime(), 0.f));

	transform->SetPosition(newRot * position);

	newRot = -newRot * transform->GetRotation();
	transform->SetRotation(newRot);
}
