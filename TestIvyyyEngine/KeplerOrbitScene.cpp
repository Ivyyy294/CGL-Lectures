#include "KeplerOrbitScene.h"
#include "IvyyyDirectionalLight.h"
#include "DebugInfo.h"
#include "IvyyyMeshRenderer.h"
#include "IvyyyTextureShaderClass.h"
#include "CameraMovement.h"
#include "GridMaterial.h"
#include "TrackMovement.h"
#include "ColorMaterial.h"
#include "IvyyyPhysicObject.h"
#include "IvyyyPhysicObjectGravityGenerator.h"
#include <random>
#include <IvyyyCircleCollider.h>
#include <IvyyyCamera.h>
#include "PlanetRings.h"

void KeplerOrbitScene::Init()
{
	Camera::MainCamera()->GetGameObject()->AddComponent<CameraMovement>();


	//Add Light
	auto light = AddGameObject<GameObject>()->AddComponent<DirectionalLight>();
	light->GetTransform()->SetParent(Camera::MainCamera()->GetTransform());
	light->SetColor(Color(1.f, 1.f, 1.f, 0.5f));

	//UI
	auto ui = AddGameObject();
	ui->transform.SetPosition(Vector3(0.f, 0.f, 0.0f));
	ui->transform.SetPivot(Transform::Pivot::TOPLEFT);
	ui->transform.SetSpace(Transform::Space::SCREEN);
	auto fontRenderer = ui->AddComponent<FontRenderer>();
	fontRenderer->SetSize(Vector2(512.f, 100.f));
	ui->AddComponent <DebugInfo>();

	//Sun
	{
		auto sun = AddPlanet(10.f, true, 1.f, Vector3::Zero, Vector3::Zero, Color::Yellow, 0);
		sun->AddComponent< PhysicObjectGravityGenerator>();
	}

	//Mercury
	AddPlanet(1.f, false, 0.15f, Vector3::Left * 1.5f, Vector3::Down * 2.6f, { 1.f, 0.5f, 0.f, 1.0f }, 100);

	//Venus
	AddPlanet(1.f, false, 0.15f, Vector3::Left * 2.f, Vector3::Down * 2.25f, { 1.f, 0.83f, 0.57f, 1.0f }, 100);

	//Earth
	AddPlanet (1.f, false, 0.15f, Vector3::Left * 2.5f, Vector3::Down * 2.f, Color::Blue, 150);

	//Mars
	AddPlanet(1.f, false, 0.15f, Vector3::Left * 3.f, Vector3::Down * 1.825f, Color::Red, 125);

	//Jupiter
	AddPlanet (1.f, false, 0.5f, Vector3::Left * 5.f, Vector3::Down * 1.425f, { 1.f, 0.8f, 0.6f, 1.0f }, 300);

	//Saturn
	auto saturn = AddPlanet(1.f, false, 0.3f, Vector3::Left * 5.5f, Vector3::Down * 1.375f, { 1.f, 1.f, 0.6f, 1.0f }, 300);
	auto saturnRings = saturn->AddComponent<PlanetRings>();
	saturnRings->SetColor({ 1.f, 1.f, 0.6f, 1.0f });
	saturnRings->SetRings ({0.2f, 0.22f, 0.24f, 0.28f, 0.3f});

	//Kupier Belt
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> offset(-10.f, 10.f); // define the range
		std::uniform_int_distribution<> angleRnd(-M_PI * 20.f, M_PI * 20.f); // define the range

		for (int i = 0; i < 600; ++i)
		{
			auto asteroid = AddGameObject();

			auto tracker = asteroid->AddComponent<TrackMovement>();
			tracker->SetColor({ 0.3, 0.3, 0.3, 1.0f });
			tracker->SetMaxLength(10);
			tracker->SetLineSpacing(0.1f);

			//asteroid->AddComponent<CircleCollider>()->SetRadius (0.5f);
			auto renderer = asteroid->AddComponent<MeshRenderer>();
			renderer->SetMesh(Mesh::Sphere(16, 16));
			auto mat = std::make_shared<ColorMaterial>();
			mat->SetColor({0.3, 0.3, 0.3, 1.0f});
			renderer->SetMaterial(mat);

			float posOffset = offset(gen) / 50.f;
			float posOffsetZ = offset(gen) / 25.f;
			float angle = angleRnd (gen) / 10.f;

			float radius = 4.f;
			float x = std::cos(angle) * radius;
			float y = std::sin(angle) * radius;

			Vector3 pos { x, y, 0.f };
			asteroid->transform.SetPosition(pos + (Vector3::Left * posOffset) + (Vector3::Forward * posOffsetZ));
			asteroid->transform.SetLocalScale({ 0.05, 0.05f, 0.05f });

			auto rb = asteroid->AddComponent<PhysicObject>();
			rb->SetMass(0.1f);
			Vector3 velocity = { -pos.y, pos.x , 0.f };
			velocity = velocity.Normalized() * 1.55f;
			rb->SetVelocity(velocity);
		}
	}
}

void KeplerOrbitScene::GridTest()
{
	auto parent = AddGameObject();

	//Grid
	auto grid = AddGameObject();
	grid->SetParent(&parent->transform);
	grid->transform.SetLocalScale({ 10.f, 10.f, 10.f });

	//grid->AddComponent<PlayerMovement>();

	auto mr = grid->AddComponent<MeshRenderer>();
	mr->SetMesh(Mesh::CornerGrid());

	auto mat = std::make_shared<GridMaterial>();
	//auto mat = std::make_shared<TextureShaderClass>();
	//mat->SetTexture (Texture::LoadTexture(L"texture_test.png"));
	mr->SetMaterial(mat);

	//Camera
	Camera::MainCamera()->GetTransform()->SetPosition({ 0.f, -1.f, -20.f });
	//Camera::MainCamera()->GetTransform()->SetRotation (Quaternion::Euler(5.f, -5.f, 0.f));

	auto cube = AddGameObject<GameObject>();
	cube->transform.SetPosition({ 0.f, -4.4f, 0.f });
	cube->transform.SetParent(&parent->transform);
	auto matCube = std::make_shared<TextureShaderClass>();
	matCube->SetTexture(Texture::LoadTexture(L"texture_test.png"));
	auto cubeRender = cube->AddComponent<MeshRenderer>();
	cubeRender->SetMesh(Mesh::CornerGrid());
	cubeRender->SetMaterial(matCube);

	//Rotate Grid
	parent->transform.SetRotation(Quaternion::Euler(-5.f, 0.f, 0.f) * Quaternion::Euler(0.f, 45.f, 0.f));
}

GameObject* KeplerOrbitScene::AddPlanet(float mass, bool isStatic, float size, Vector3 position, Vector3 velocity, Color color, int trackLength)
{
	auto planet = AddGameObject();

	auto tracker = planet->AddComponent<TrackMovement>();
	tracker->SetColor(color);
	tracker->SetMaxLength (trackLength);
	tracker->SetLineSpacing (0.25f);

	auto renderer = planet->AddComponent<MeshRenderer>();
	renderer->SetMesh(Mesh::Sphere(16, 16));
	auto mat = std::make_shared<ColorMaterial>();
	mat->SetColor(color);
	renderer->SetMaterial(mat);

	planet->transform.SetPosition(position);
	planet->transform.SetLocalScale({ size, size, size });

	auto rb = planet->AddComponent<PhysicObject>();
	rb->SetStatic(isStatic);
	rb->SetVelocity(velocity);
	rb->SetMass(mass);

	return planet;
}
