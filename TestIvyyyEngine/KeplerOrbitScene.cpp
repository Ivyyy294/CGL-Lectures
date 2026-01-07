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
#include "IvyyyTime.h"
#include "IvyyyMathF.h"

void KeplerOrbitScene::Init()
{
	Time::SetTimeScale(0.5f);
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
		auto sun = AddPlanet(10.f, true, 0.3f, Vector3::Zero, Vector3::Zero, Color::Yellow, 0, 0.f);
		sun->AddComponent< PhysicObjectGravityGenerator>();
		soi = sun->GetComponent<PhysicObject>().get();
	}

	//TestPlanet
	//PlanetData testPlanet{ 1.f, 0.1f, { 1.f, 1.f, 1.f, 1.0f }, false, {1.0, 0.2f, 45.0f, 90.0f, 45.0f}, 100, 0.05f };
	//AddPlanet(testPlanet, soi);

	//Mercury
	PlanetData mercury{ 1.f, 0.1f, { 1.f, 0.5f, 0.f, 1.0f }, false, {0.387098f, 0.205630f, 6.35f, 48.331f, 29.124f}, 34, 0.05f };
	AddPlanet(mercury, soi);

	//Venus
	PlanetData venus {1.f, 0.15f, { 1.f, 0.83f, 0.57f, 1.0f }, false, {0.723332f, 0.006772f, 2.15f, 76.680f, 54.884f}, 59, 0.05f};
	AddPlanet(venus, soi);

	//Earth
	PlanetData earth {1.f, 0.15f, Color::Blue, false, {1.000003f, 0.0167086f, 0.00005f, -11.26064f, 114.20783f}, 97, 0.05f};
	AddPlanet (earth, soi)->GetComponent<PhysicObject>();

	//Mars
	PlanetData mars{ 1.f, 0.1f, Color::Red, false, {1.52371f, 0.0934f, 1.63f, 49.57854f, 286.5f}, 156, 0.05f };
	AddPlanet(mars, soi);

	//Jupiter
	PlanetData jupiter{ 1.f, 0.89f, { 1.f, 0.8f, 0.6f, 1.0f }, false, {5.2029f, 0.0489f, 0.32f, 100.464f, 273.867f}, 300, 0.2f };
	AddPlanet(jupiter, soi);

	//Saturn
	PlanetData saturn{ 1.f, 0.74f, { 1.f, 1.f, 0.6f, 1.0f }, false, {9.537f, 0.0565f, 0.93f, 113.665f, 339.392f}, 500, 0.1f };
	auto saturnRings = AddPlanet(saturn, soi)->AddComponent<PlanetRings>();
	saturnRings->SetColor({ 1.f, 1.f, 0.6f, 1.0f });
	saturnRings->SetRings ({0.4f, 0.42f, 0.43f, 0.46f, 0.48f, 0.51f, 0.53f, 0.55f});

	//Uranus
	PlanetData uranus{ 1.f, 0.32f, { 0.47f, 0.78f, 0.8f, 1.0f }, false, {19.189f, 0.04717f, 0.99f, 74.006f, 96.998857f}, 300, 0.1f };
	AddPlanet(uranus, soi);

	//Neptun
	PlanetData neptun{ 1.f, 0.31f, { 0.57f, 0.8f, 0.94f, 1.0f }, false, {30.0699f, 0.008678, 0.74f, 131.783f, 273.187f}, 300, 0.1f };
	AddPlanet(neptun, soi);

	//Pluto
	PlanetData pluto{ 1.f, 0.05f, { 0.4f, 0.34f, 0.30f, 1.0f }, false, {39.482f, 0.2488f, 17.16f, 110.299f, 113.834f}, 300, 0.1f };
	AddPlanet(pluto, soi);


	//Kupier Belt
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> smaRnd(25.f, 35.f); // define the range
		std::uniform_int_distribution<> eRnd(0.f, 0.5f); // define the range
		std::uniform_int_distribution<> iRnd(-10.f, 10.f); // define the range
		std::uniform_int_distribution<> oRnd(0.f, 360.f); // define the range
		std::uniform_int_distribution<> wRnd(0.f, 360.f); // define the range

		for (int j = 0; j < 300; ++j)
		{
			float sma = smaRnd(gen) * 0.1f;
			float e = eRnd(gen);
			float i = iRnd(gen);
			float o = oRnd(gen);
			float w = wRnd(gen);

			PlanetData asteroid{ 0.1f, 0.025f, { 0.3, 0.3, 0.3, 1.0f }, false, {sma, e, i, o, w}, 0, 0.05f };
			AddPlanet (asteroid, soi);
		}
	}

	//Outer belt
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> smaRnd(350.f, 400.f); // define the range
		std::uniform_int_distribution<> eRnd(0.f, 0.5f); // define the range
		std::uniform_int_distribution<> iRnd(-90.f, 90.f); // define the range
		std::uniform_int_distribution<> oRnd(0.f, 360.f); // define the range
		std::uniform_int_distribution<> wRnd(0.f, 360.f); // define the range
		std::uniform_int_distribution<> sizeRnd(25, 200); // define the range

		for (int j = 0; j < 1000; ++j)
		{
			float sma = smaRnd(gen) * 0.1f;
			float e = eRnd(gen);
			float i = iRnd(gen);
			float o = oRnd(gen);
			float w = wRnd(gen);
			float size = sizeRnd (gen) * 0.001f;

			PlanetData star{ 0.1f, size, { 0.3, 0.3, 0.3, 1.0f }, false, {sma, e, i, o, w}, 0, 0.05f };
			AddPlanet(star, soi);
		}
	}
}

GameObject* KeplerOrbitScene::AddPlanet(float mass, bool isStatic, float size, Vector3 position, Vector3 velocity, Color color, int trackLength, float lineSpacing)
{
	auto planet = AddGameObject();

	auto tracker = planet->AddComponent<TrackMovement>();
	tracker->SetColor(color);
	tracker->SetMaxLength (trackLength);
	tracker->SetLineSpacing (0.25f);
	tracker->SetLineSpacing (lineSpacing);

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
	//Apply Longitude of ascending node
	Vector3 ascendingNodeDir = Vector3::Down;
	Vector3 orbitalPlaneNormal = Vector3::Back;

	Quaternion o = Quaternion::AroundAxis(Vector3::Forward, data.orbit.o * MathF::Deg2Rad);

	ascendingNodeDir = o * ascendingNodeDir;
	orbitalPlaneNormal = o * orbitalPlaneNormal;

	//Apply inclination
	Quaternion i = Quaternion::AroundAxis(ascendingNodeDir, -data.orbit.i * MathF::Deg2Rad);

	orbitalPlaneNormal = i * orbitalPlaneNormal;

	Vector3 periabsisDir = orbitalPlaneNormal.Cross(ascendingNodeDir);
	
	//Apply Argument of periapsis
	Quaternion w = Quaternion::AroundAxis(orbitalPlaneNormal, -data.orbit.w * MathF::Deg2Rad);

	periabsisDir = w * periabsisDir;

	//Callculate velocity

	float c = data.orbit.e * data.orbit.a;

	Vector3 f1 = soi->GetTransform()->GetPosition();

	Vector3 center = f1 - periabsisDir * c;

	Vector3 v1 = center + (periabsisDir * data.orbit.a);

	float r = (v1-f1).Magnitude();

	float v = sqrtf(soi->GetMass() * (2.f / r - 1.f / data.orbit.a ));

	Vector3 velDir = periabsisDir.Cross(orbitalPlaneNormal);
	Vector3 velocity = velDir * v;

	Vector3 orbitPlaneNormal = ascendingNodeDir.Cross (periabsisDir);
	
	return AddPlanet(data.mass, data.isStatic, data.radius, v1, velocity, data.color, data.trackLength, data.lineSpacing);
}
