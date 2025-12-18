#include "SpaceCoonScene.h"
#include "Player.h"
#include "IvyyyPhysicObject.h"
#include "IvyyyRectCollider.h"
#include <random>
#include "IvyyyMeshRenderer.h"
#include "IvyyyTextureShaderClass.h"
#include "IvyyyCircleCollider.h"
#include "ColorShader.h"
#include "PlayerMovement.h"
#include "IvyyySpriteRenderer.h"
#include "IvyyyFontRenderer.h"
#include "DebugInfo.h"

void SpaceCoonScene::Init()
{
	//auto circle = AddGameObject();
	//auto meshrender = circle->AddComponent<MeshRenderer>();
	//meshrender->SetMesh(Mesh::Circle(64));
	////meshrender->SetMesh(Mesh::Quad());
	//meshrender->SetShader <SpriteRenderer>();

	SpawnPlayer();
	SpawnAsteroid();
	SpawnColliders();
	SpawnUi();
}

void SpaceCoonScene::SpawnPlayer()
{
	Mesh cube;
	cube.LoadModel("cube.txt");

	//Parent cube
	auto player = AddGameObject<GameObject>(Vector3(960.f, -540.f, 0.f));
	player->transform.SetSpace(Transform::Space::SCREEN);
	auto meshRenderer = player->AddComponent<SpriteRenderer>();
	meshRenderer->SetSize({96.f, 96.f});

	meshRenderer->SetShader <TextureShaderClass>();
	meshRenderer->SetMesh (Mesh::Quad());

	//meshRenderer->SetShader <ColorShader>();
	//meshRenderer->SetMesh(Mesh::Circle(64));

	((TextureShaderClass*)meshRenderer->GetShader())->SetTexture(Texture::LoadTexture(L"player.png"));
	player->AddComponent<CircleCollider>()->SetRadius(96.f * 0.5f);
	player->AddComponent<PlayerMovement>();
	auto pPhy = player->AddComponent<PhysicObject>();
	pPhy->SetLinearDamping(0.0f);
	pPhy->SetMass(5.f);
}

void SpaceCoonScene::SpawnAsteroid()
{
	//Spawn Asteroids

	for (int i = 0; i < 16; ++i)
		SpawnAsteroid(128.f, 5.f);

	for (int i = 0; i < 96; ++i)
		SpawnAsteroid(80.f, 3.f);

	for (int i = 0; i < 48; ++i)
		SpawnAsteroid(48.f, 1.f);
}

void SpaceCoonScene::SpawnAsteroid(float size, float mass)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distrPosX(100, 1880); // define the range
	std::uniform_int_distribution<> distrPosY(100, 980); // define the range
	std::uniform_int_distribution<> distrVel(-20, 20); // define the range

	float x = distrPosX(gen);
	float y = distrPosY(gen) * -1.f;
	float vel = distrVel(gen);

	auto asteroid = AddGameObject<GameObject>(Vector3(x, y, 0.f));
	//asteroid->transform.SetLocalScale(Vector3(size, size, size));
	asteroid->transform.SetSpace(Transform::Space::SCREEN);
	asteroid->AddComponent<CircleCollider>()->SetRadius(size * 0.5f);

	//Parent cube
	auto meshRenderer = asteroid->AddComponent<SpriteRenderer>();

	meshRenderer->SetMesh(Mesh::Quad());
	meshRenderer->SetShader <TextureShaderClass>();
	((TextureShaderClass*)meshRenderer->GetShader())->SetTexture(Texture::LoadTexture(L"Asteroid_128.png"));

	//meshRenderer->SetShader <ColorShader>();
	//meshRenderer->SetMesh(Mesh::Circle(64));

	meshRenderer->SetSize({ size, size });

	auto physic = asteroid->AddComponent<PhysicObject>();
	physic->SetMass(mass * 2.f);
	physic->SetVelocity(Vector3(vel, vel, 0.f));
}

void SpaceCoonScene::SpawnColliders()
{
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

void SpaceCoonScene::SpawnUi()
{
	auto ui = AddGameObject();
	ui->transform.SetPosition(Vector3(0.f, 0.f,0.0f));
	ui->transform.SetPivot(Transform::Pivot::TOPLEFT);
	ui->transform.SetSpace(Transform::Space::SCREEN);

	auto fontRenderer = ui->AddComponent<FontRenderer>();
	fontRenderer->SetText(L"Hello World!");
	fontRenderer->SetSize (Vector2(512.f, 100.f));

	ui->AddComponent <DebugInfo>();
}
