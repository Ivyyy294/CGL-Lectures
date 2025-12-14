#include "PlayerMovement.h"
#include "IvyyyInput.h"
#include "IvyyyTime.h"
#include "IvyyyDebug.h"

using namespace Ivyyy;

void PlayerMovement::Update ()
{
	Vector2 moveVec;

	//Horizontal movement
	if (Input::KeyPressed (Key::KEY_D))
		moveVec += Vector2::Right;
	if (Input::KeyPressed (Key::KEY_A))
		moveVec -= Vector2::Right;
	
	//Vertical movement
	if (Input::KeyPressed (Key::KEY_W))
		moveVec += Vector3::Up;
	if (Input::KeyPressed (Key::KEY_S))
		moveVec -= Vector3::Up;

	//Scale
	if (Input::KeyPressed(Key::KEY_F))
	{
		Vector3 scale = transform->GetLocalScale();
		scale = scale * (1.f - Time::DeltaTime());
		transform->SetLocalScale (scale);
	}
	if (Input::KeyPressed (Key::KEY_G))
	{
		Vector3 newScale = transform->GetLocalScale() * (1.f + Time::DeltaTime());
		transform->SetLocalScale(newScale);
	}

	//Rotation
	if (Input::KeyPressed(Key::KEY_UP))
	{
		Quaternion euler = Quaternion::Euler(Vector3(45.f * Time::DeltaTime(), 0.f, 0.f));
		Quaternion newRot = euler * transform->GetRotation();
		transform->SetRotation(newRot);
	}

	if (Input::KeyPressed(Key::KEY_DOWN))
	{
		Quaternion euler = Quaternion::Euler(Vector3(-45.f * Time::DeltaTime(), 0.f, 0.f));
		Quaternion newRot = euler * transform->GetRotation();
		transform->SetRotation(newRot);
	}

	if (Input::KeyPressed(Key::KEY_RIGHT))
	{
		Quaternion euler = Quaternion::Euler (Vector3 (0.f, -45.f * Time::DeltaTime(), 0.f));
		Quaternion newRot = euler * transform->GetRotation();
		transform->SetRotation(newRot);
	}

	if (Input::KeyPressed(Key::KEY_LEFT))
	{
		Quaternion euler = Quaternion::Euler(Vector3(0.f, 45.f * Time::DeltaTime(), 0.f));
		Quaternion newRot = euler * transform->GetRotation();
		transform->SetRotation(newRot);
	}

	if (Input::KeyPressed(Key::KEY_Z))
	{
		Quaternion euler = Quaternion::Euler(Vector3(0.f, 0.f, 45.f * Time::DeltaTime()));
		Quaternion newRot = euler * transform->GetRotation();
		transform->SetRotation(newRot);
	}


	Vector3 newPos = transform->GetLocalPosition() + moveVec.Normalized() * speed * Time::DeltaTime();
	transform->SetLocalPosition(newPos);
}

void PlayerMovement::OnMouseDown()
{
	Debug::Log ("Mouse Down!");
}
