#include "CameraMovement.h"
#include "IvyyyInput.h"
#include "IvyyyTime.h"

void CameraMovement::Update()
{
	//Vector3 moveVec = Vector3::Zero;
	////Horizontal movement
	//if (Input::KeyPressed(Key::KEY_D))
	//	moveVec += Vector3::Left;

	//if (Input::KeyPressed(Key::KEY_A))
	//	moveVec += Vector3::Right;

	////Vertical movement
	//if (Input::KeyPressed(Key::KEY_W))
	//	moveVec += Vector3::Down;
	//if (Input::KeyPressed(Key::KEY_S))
	//	moveVec += Vector3::Up;

	Quaternion currentRot = transform->GetRotation();
	Vector3 position = transform->GetPosition();
	Quaternion newRot = Quaternion::Identity;

	//Rotation
	if (Input::KeyPressed(Key::KEY_UP))
		newRot = newRot * Quaternion::Euler(currentRot * Vector3(-45.f * Time::DeltaTime(), 0.f, 0.f));

	if (Input::KeyPressed(Key::KEY_DOWN))
		newRot = newRot * Quaternion::Euler(currentRot * Vector3(45.f * Time::DeltaTime(), 0.f, 0.f));

	if (Input::KeyPressed(Key::KEY_RIGHT))
		newRot = newRot * Quaternion::Euler(currentRot * Vector3(0.f, -45.f * Time::DeltaTime(), 0.f));
	if (Input::KeyPressed(Key::KEY_LEFT))
		newRot = newRot * Quaternion::Euler(currentRot * Vector3(0.f, 45.f * Time::DeltaTime(), 0.f));

	transform->SetPosition(newRot * position);

	newRot = -newRot * transform->GetRotation();
	transform->SetRotation(newRot);
}
