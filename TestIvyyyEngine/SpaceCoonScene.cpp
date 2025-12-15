#include "SpaceCoonScene.h"
#include "Player.h"
#include "IvyyyPhysicObject.h"
#include "IvyyyRectCollider.h"
#include <random>
#include "IvyyyMeshRenderer.h"
#include "TextureShaderClass.h"
#include "IvyyyCircleCollider.h"
#include "ColorShader.h"
#include "PlayerMovement.h"
#include "IvyyySpriteRenderer.h"

void SpaceCoonScene::Init()
{
	Mesh cube;
	cube.LoadModel("cube.txt");

	//Parent cube
	auto player = AddGameObject<GameObject>(Vector3 (960.f, -540.f, 0.f));
	player->transform.SetSpace (Transform::Space::SCREEN);
	auto meshRenderer = player->AddComponent<SpriteRenderer>();
	meshRenderer->SetShader <TextureShaderClass>();
	((TextureShaderClass*)meshRenderer->GetShader())->SetTexture(Texture::LoadTexture(L"player.png"));
	player->AddComponent<CircleCollider>()->SetRadius(96.f * 0.5f);
	player->AddComponent<PlayerMovement>();
	auto pPhy = player->AddComponent<PhysicObject>();
	pPhy->SetLinearDamping(0.0f);
	pPhy->SetMass (5.f);

	//Spawn Asteroids

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distrPosX(100, 1880); // define the range
	std::uniform_int_distribution<> distrPosY(100, 980); // define the range
	std::uniform_int_distribution<> distrMass(1, 5); // define the range
	std::uniform_int_distribution<> distrVel(-20, 20); // define the range

	for (int i = 0; i < 32; ++i)
	{
		float x = distrPosX(gen);
		float y = distrPosY(gen) * -1.f;
		float mass = distrMass(gen);
		float size = 0.25f + 1.f / (5.f - mass);
		float vel = distrVel(gen);

		auto asteroid = AddGameObject<GameObject>(Vector3(x, y, 0.f));
		//asteroid->transform.SetLocalScale(Vector3(0.25f, 0.25f, 0.25f));
		asteroid->transform.SetSpace(Transform::Space::SCREEN);
		asteroid->AddComponent<CircleCollider>()->SetRadius(128.f * 0.5f);
		asteroid->transform.SetLocalScale(Vector3(size, size, size));

		//Parent cube
		auto meshRenderer = asteroid->AddComponent<SpriteRenderer>();
		meshRenderer->SetMesh(Mesh::Quad());
		meshRenderer->SetShader <TextureShaderClass>();
		((TextureShaderClass*)meshRenderer->GetShader())->SetTexture(Texture::LoadTexture(L"Asteroid_128.png"));

		auto physic = asteroid->AddComponent<PhysicObject>();
		physic->SetMass(mass * 2.f);
		physic->SetVelocity(Vector3(vel, vel, 0.f));
	}

	//Add Light
	auto light = AddGameObject<GameObject>()->AddComponent<DirectionalLight>();
	light->SetColor(Color(1.f, 1.f, 1.f, 0.5f));

	//add colliders
	auto colliderTop = AddGameObject<GameObject>(Vector3(960.0f, 0.f, 0.f));
	colliderTop->transform.SetSpace(Transform::Space::SCREEN);
	colliderTop->AddComponent<RectCollider>()->SetSize(1920, 100);

	auto colliderBottom = AddGameObject<GameObject>(Vector3(960.0f, -1080.0f, 0.f));
	colliderBottom->transform.SetSpace(Transform::Space::SCREEN);
	colliderBottom->AddComponent<RectCollider>()->SetSize(1920, 100);

	auto colliderLeft = AddGameObject<GameObject>(Vector3(-25.f, -540.f, 0.f));
	colliderLeft->transform.SetSpace(Transform::Space::SCREEN);
	colliderLeft->AddComponent<RectCollider>()->SetSize(100, 1080.f);

	auto colliderRight = AddGameObject<GameObject>(Vector3(1920.f + 25.f, -540.f, 0.f));
	colliderRight->transform.SetSpace(Transform::Space::SCREEN);
	colliderRight->AddComponent<RectCollider>()->SetSize(100, 1080.f);
}
