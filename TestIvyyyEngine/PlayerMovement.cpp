#include "PlayerMovement.h"
#include "IvyyyInput.h"
#include "IvyyyTime.h"
#include "IvyyyDebug.h"
#include "IvyyyPhysicObject.h"
#include "IvyyyGizmo.h"

using namespace Ivyyy;

void PlayerMovement::Start()
{
	if (Ivyyy::Renderer::GetMode() == Ivyyy::Renderer::Mode::D2D
	|| gameObject->transform.GetSpace() == Transform::Space::SCREEN)
		speed = 512.0f;
}

void PlayerMovement::Update ()
{
	//Horizontal movement
	if (Input::KeyPressed (Key::KEY_D))
		moveVec += Vector3::Right;

	if (Input::KeyPressed (Key::KEY_A))
		moveVec -= Vector3::Right;
	
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

	Vector3 newPos = moveVec.Normalized() * speed * Time::DeltaTime();
	auto obj = gameObject->GetComponent<PhysicObject>();

	if (obj != nullptr)
		obj->ApplyImpulse(newPos * obj->GetMass());

	moveVec = Vector3::Zero;
}

void PlayerMovement::OnMouseDown()
{
	Debug::Log ("Mouse Down!");
}
