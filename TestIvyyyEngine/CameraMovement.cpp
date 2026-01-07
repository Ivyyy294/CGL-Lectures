#include "CameraMovement.h"
#include "IvyyyInput.h"
#include "IvyyyTime.h"
#include "IvyyyDraw.h"
#include "ReferenceFrame.h"

void CameraMovement::Update()
{
	float rotSpeed = 45.f;
	float moveSpeed = 50.f;

	Quaternion currentRot = transform->GetRotation();
	Vector3 position = transform->GetPosition();
	Quaternion newRot = Quaternion::Identity;

	//Rotation
	if (Input::KeyPressed(Key::KEY_UP))
		newRot = newRot * Quaternion::Euler(currentRot * Vector3(-rotSpeed * Time::UnscaledDeltaTime(), 0.f, 0.f));

	if (Input::KeyPressed(Key::KEY_DOWN))
		newRot = newRot * Quaternion::Euler(currentRot * Vector3(rotSpeed * Time::UnscaledDeltaTime(), 0.f, 0.f));

	if (Input::KeyPressed(Key::KEY_RIGHT))
		newRot = newRot * Quaternion::Euler(currentRot * Vector3(0.f, rotSpeed * Time::UnscaledDeltaTime(), 0.f));
	if (Input::KeyPressed(Key::KEY_LEFT))
		newRot = newRot * Quaternion::Euler(currentRot * Vector3(0.f, -rotSpeed * Time::UnscaledDeltaTime(), 0.f));

	transform->SetPosition(newRot * position);

	newRot = -newRot * transform->GetRotation();
	transform->SetRotation(newRot);


	//Position
	Vector3 direction = transform->GetPosition().Normalized();

	float distCap = 100.f;

	float t = transform->GetPosition().Magnitude() / distCap;

	if (t > 1.f)
		t = 1.f;

	float speed = moveSpeed * t;

	if (Input::KeyPressed(Key::KEY_W))
		transform->SetPosition(transform->GetPosition() - direction * speed * Time::UnscaledDeltaTime());
	if (Input::KeyPressed(Key::KEY_S))
		transform->SetPosition(transform->GetPosition() + direction * speed * Time::UnscaledDeltaTime());

	//Time
	float scale = Time::TimeScale();
	float maxTimeWarp = 10.f;

	if (Input::KeyPressed(Key::KEY_D))
		scale += Time::UnscaledDeltaTime() * 2.f;
	if (Input::KeyPressed(Key::KEY_A))
		scale -= Time::UnscaledDeltaTime() * 2.f;

	if (scale > maxTimeWarp)
		scale = maxTimeWarp;
	if (scale < -maxTimeWarp)
		scale = -maxTimeWarp;

	Time::SetTimeScale(scale);
}
