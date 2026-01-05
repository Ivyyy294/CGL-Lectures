#include "KeplerOrbitScene.h"
#include "IvyyyDirectionalLight.h"
#include "DebugInfo.h"
#include "IvyyyMeshRenderer.h"
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

	PhysicObject* soi = nullptr;
	//Sun
	{
		auto sun = AddPlanet(10.f, true, 2.f, Vector3::Zero, Vector3::Zero, Color::Yellow, 0);
		sun->AddComponent< PhysicObjectGravityGenerator>();
		soi = sun->GetComponent<PhysicObject>().get();
	}

	//Mercury
	PlanetData mercury{ 1.f, 0.1f, { 1.f, 0.5f, 0.f, 1.0f }, false, {1.5f, 0.f}, 100 };
	AddPlanet(mercury, soi);

	//Venus
	PlanetData venus {1.f, 0.15f, { 1.f, 0.83f, 0.57f, 1.0f }, false, {2., 0.f}, 100};
	AddPlanet(venus, soi);

	//Earth
	PlanetData earth {1.f, 0.15f, Color::Blue, false, {2.5f, 0.f}, 150};
	AddPlanet (earth, soi);

	//Mars
	PlanetData mars{ 1.f, 0.1f, Color::Red, false, {3.f, 0.f}, 150 };
	AddPlanet(mars, soi);

	//Jupiter
	PlanetData jupiter{ 1.f, 0.89f, { 1.f, 0.8f, 0.6f, 1.0f }, false, {4.75f, 0.f}, 300 };
	AddPlanet(jupiter, soi);

	//Saturn
	PlanetData saturn{ 1.f, 0.74f, { 1.f, 1.f, 0.6f, 1.0f }, false, {5.75f, 0.f}, 300 };
	auto saturnRings = AddPlanet(saturn, soi)->AddComponent<PlanetRings>();
	saturnRings->SetColor({ 1.f, 1.f, 0.6f, 1.0f });
	saturnRings->SetRings ({0.4f, 0.42f, 0.43f, 0.46f, 0.48f, 0.51f, 0.53f, 0.55f});

	//Uranus
	PlanetData uranus{ 1.f, 0.32f, { 0.47f, 0.78f, 0.8f, 1.0f }, false, {6.75f, 0.f}, 300 };
	AddPlanet(uranus, soi);

	//Neptun
	PlanetData neptun{ 1.f, 0.31f, { 0.57f, 0.8f, 0.94f, 1.0f }, false, {7.25f, 0.f}, 300 };
	AddPlanet(neptun, soi);

	//Pluto
	PlanetData pluto{ 1.f, 0.05f, { 0.4f, 0.34f, 0.30f, 1.0f }, false, {7.75f, 0.f}, 300 };
	AddPlanet(pluto, soi);


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
			tracker->SetMaxLength(5);
			tracker->SetLineSpacing(0.1f);

			//asteroid->AddComponent<CircleCollider>()->SetRadius (0.5f);
			auto renderer = asteroid->AddComponent<MeshRenderer>();
			renderer->SetMesh(Mesh::Sphere(16, 16));
			auto mat = std::make_shared<ColorMaterial>();
			mat->SetColor({0.3, 0.3, 0.3, 1.0f});
			renderer->SetMaterial(mat);

			float posOffset = offset(gen) / 40.f;
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

GameObject* KeplerOrbitScene::AddPlanet(const PlanetData& data, const PhysicObject* soi)
{
	float c = data.orbit.e * data.orbit.a;

	Vector3 f1 = soi->GetTransform()->GetPosition();
	Vector3 center = f1 - (f1.Normalized() * c);

	Vector3 direction = f1-center;

	if (direction.Magnitude() <= 0.f)
		direction = Vector3::Left;

	Vector3 v1 = center + (direction * data.orbit.a);

	float r = (v1-f1).Magnitude();

	float v = sqrtf(soi->GetMass() * (2.f / r - 1.f / data.orbit.a ));

	Vector3 velocity = Vector3::Down * v;

	return AddPlanet (data.mass, data.isStatic, data.radius, v1, velocity, data.color, data.trackLength);
}
