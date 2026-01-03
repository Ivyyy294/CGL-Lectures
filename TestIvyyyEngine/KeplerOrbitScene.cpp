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

	auto parent = AddGameObject();

	//Sun
	{
		auto sun = AddGameObject();
		sun->SetParent (parent);
		auto renderer = sun->AddComponent<MeshRenderer>();
		renderer->SetMesh(Mesh::Sphere(16, 16));
		auto mat = std::make_shared<ColorMaterial>();
		mat->SetColor (Color::Yellow);
		renderer->SetMaterial (mat);

		auto rb = sun->AddComponent<PhysicObject>();
		rb->SetStatic (true);
		rb->SetMass (10.f);

		sun->AddComponent< PhysicObjectGravityGenerator>();
	}

	//Mercury
	{
		auto mercury = AddGameObject();
		mercury->SetParent(parent);
		auto renderer = mercury->AddComponent<MeshRenderer>();
		mercury->AddComponent<TrackMovement>()->SetColor({ 1.f, 0.5f, 0.f, 1.0f });
		renderer->SetMesh(Mesh::Sphere(16, 16));
		auto mat = std::make_shared<ColorMaterial>();
		mat->SetColor({1.f, 0.5f, 0.f, 1.0f});
		renderer->SetMaterial(mat);

		mercury->transform.SetPosition(Vector3::Left * 1.5f);
		mercury->transform.SetLocalScale({ 0.25, 0.25f, 0.25f });

		auto rb = mercury->AddComponent<PhysicObject>();
		rb->SetVelocity(Vector3::Down * 2.6f);
		rb->SetMass(1.f);
	}

	//Mars
	{
		auto mars = AddGameObject();
		mars->SetParent(parent);
		mars->AddComponent<TrackMovement>()->SetColor(Color::Red);
		auto renderer = mars->AddComponent<MeshRenderer>();
		renderer->SetMesh(Mesh::Sphere(16, 16));
		auto mat = std::make_shared<ColorMaterial>();
		mat->SetColor(Color::Red);
		renderer->SetMaterial(mat);

		mars->transform.SetPosition(Vector3::Left * 2.f);
		mars->transform.SetLocalScale({ 0.25, 0.25f, 0.25f });

		auto rb = mars->AddComponent<PhysicObject>();
		rb->SetVelocity(Vector3::Down * 2.25f);
		rb->SetMass(1.f);
	}

	//Earth
	{
		auto earth = AddGameObject();
		earth->SetParent(parent);
		earth->AddComponent<TrackMovement>()->SetColor(Color::Blue);
		auto renderer = earth->AddComponent<MeshRenderer>();
		renderer->SetMesh(Mesh::Sphere(16, 16));
		auto mat = std::make_shared<ColorMaterial>();
		mat->SetColor(Color::Blue);
		renderer->SetMaterial(mat);

		earth->transform.SetPosition (Vector3::Left * 2.5f);
		earth->transform.SetLocalScale ({0.25, 0.25f, 0.25f});

		auto rb = earth->AddComponent<PhysicObject>();
		rb->SetVelocity (Vector3::Down * 2.f);
		rb->SetMass(1.f);
	}

	//Jupiter
	{
		auto jupiter = AddGameObject();
		jupiter->SetParent(parent);
		jupiter->AddComponent<TrackMovement>()->SetColor({1.f, 1.f, 0.6f, 1.0f});
		auto renderer = jupiter->AddComponent<MeshRenderer>();
		renderer->SetMesh(Mesh::Sphere(16, 16));
		auto mat = std::make_shared<ColorMaterial>();
		mat->SetColor({ 1.f, 1.f, 0.6f, 1.0f });
		renderer->SetMaterial(mat);

		jupiter->transform.SetPosition(Vector3::Left * 5.5f);
		jupiter->transform.SetLocalScale({ 0.5, 0.5f, 0.5f });

		auto rb = jupiter->AddComponent<PhysicObject>();
		rb->SetVelocity(Vector3::Down * 1.35f);
		rb->SetMass(1.f);
	}

	//Kupier Belt
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> offset(-10.f, 10.f); // define the range
		std::uniform_int_distribution<> angleRnd(-M_PI * 20.f, M_PI * 20.f); // define the range

		for (int i = 0; i < 600; ++i)
		{
			auto asteroid = AddGameObject();
			//asteroid->AddComponent<TrackMovement>()->SetColor({ 0.3, 0.3, 0.3, 1.0f });
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
