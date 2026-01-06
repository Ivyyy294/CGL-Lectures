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

	Vector3 direction = transform->GetPosition().Normalized();
	float maxSpeed = 50.f;
	float distCap = 100.f;

	float t = transform->GetPosition().Magnitude() / distCap;

	if (t > 1.f)
		t = 1.f;

	float speed = maxSpeed * t;

	if (Input::KeyPressed(Key::KEY_W))
		transform->SetPosition(transform->GetPosition() - direction * speed * Time::DeltaTime());
	if (Input::KeyPressed(Key::KEY_S))
		transform->SetPosition(transform->GetPosition() + direction * speed * Time::DeltaTime());
}
