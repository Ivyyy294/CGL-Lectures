#include "SpaceCoonScene.h"
#include "Player.h"
#include "IvyyyPhysicObject.h"
#include "IvyyyRectCollider.h"
#include <random>
#include "IvyyyMeshRenderer.h"
#include "IvyyyTextureShaderClass.h"
#include "IvyyyCircleCollider.h"
#include "PlayerMovement.h"
#include "IvyyySpriteRenderer.h"
#include "IvyyyFontRenderer.h"
#include "DebugInfo.h"
#include "IvyyyConstantGravity.h"
#include "IvyyyPhysicObjectGravityGenerator.h"
#include "IvyyyGizmo.h"

void SpaceCoonScene::Init()
{
	Gizmo::Draw = true;
	SpawnPlayer();
	SpawnAsteroid();
	SpawnColliders();
	SpawnUi();

	//AddGameObject()->AddComponent<ConstantGravity>();
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

	auto playerMat = std::make_shared<TextureShaderClass>();
	playerMat->SetTexture(Texture::LoadTexture(L"player.png"));

	meshRenderer->SetMaterial(playerMat);
	meshRenderer->SetMesh (Mesh::Quad());

	//meshRenderer->SetMaterial <ColorMaterial>();
	//meshRenderer->SetMesh(Mesh::Circle(64));

	player->AddComponent<CircleCollider>()->SetRadius(96.f * 0.5f);
	player->AddComponent<PlayerMovement>();
	auto pPhy = player->AddComponent<PhysicObject>();
	pPhy->SetLinearDamping(0.0f);
	pPhy->SetMass(128.f);
}

void SpaceCoonScene::SpawnAsteroid()
{
	auto mat = std::make_shared<TextureShaderClass>();
	mat->SetTexture(Texture::LoadTexture(L"Asteroid_128.png"));

	int mod = 1;
	//Spawn Asteroids
	//for (int i = 0; i < 16; ++i)
	//	SpawnAsteroid(128.f, 32.f, mat);

	//for (int i = 0; i < 48 * mod; ++i)
	//	SpawnAsteroid(64.f, 4.f, mat);

	for (int i = 0; i < 144 * mod; ++i)
		SpawnAsteroid(32.f, 2.f, mat);

	for (int i = 0; i < 432 * mod; ++i)
		SpawnAsteroid(16.f, 1.f, mat);
}

void SpaceCoonScene::SpawnAsteroid(float size, float mass, MeshMaterial::Ptr material)
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
	meshRenderer->SetMaterial (material);

	//meshRenderer->SetMaterial <ColorMaterial>();
	//meshRenderer->SetMesh(Mesh::Circle(64));

	meshRenderer->SetSize({ size, size });

	auto physic = asteroid->AddComponent<PhysicObject>();
	physic->SetMass(mass * 2.f);
	physic->SetVelocity(Vector3(vel, vel, 0.f));
	physic->SetLinearDamping(0.2f);
}

void SpaceCoonScene::SpawnColliders()
{
	//Add Light
	auto light = AddGameObject<GameObject>()->AddComponent<DirectionalLight>();
	light->SetColor(Color(1.f, 1.f, 1.f, 0.5f));

	//add colliders
	auto colliderTop = AddGameObject<GameObject>(Vector3(960.0f, 49.f, 0.f));
	colliderTop->transform.SetSpace(Transform::Space::SCREEN);
	colliderTop->AddComponent<RectCollider>()->SetSize(1920, 100);

	auto colliderBottom = AddGameObject<GameObject>(Vector3(960.0f, -1080.0f - 50.f, 0.f));
	colliderBottom->transform.SetSpace(Transform::Space::SCREEN);
	colliderBottom->AddComponent<RectCollider>()->SetSize(1920, 100);

	auto colliderLeft = AddGameObject<GameObject>(Vector3(-49.f, -540.f, 0.f));
	colliderLeft->transform.SetSpace(Transform::Space::SCREEN);
	colliderLeft->AddComponent<RectCollider>()->SetSize(100, 1080.f);

	auto colliderRight = AddGameObject<GameObject>(Vector3(1920.f + 50.f, -540.f, 0.f));
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
