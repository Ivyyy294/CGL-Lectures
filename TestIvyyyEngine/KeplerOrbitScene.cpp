#include "IvyyyDirectionalLight.h"
#include "IvyyyMeshRenderer.h"
#include <random>
#include "IvyyyPhysicObject.h"
#include "IvyyyPhysicObjectGravityGenerator.h"
#include <IvyyyCircleCollider.h>
#include <IvyyyCamera.h>
#include "IvyyyTime.h"
#include "IvyyyMathF.h"

#include "DebugInfo.h"
#include "CameraMovement.h"
#include "GridMaterial.h"
#include "TrackMovement.h"
#include "ColorMaterial.h"
#include "PlanetRings.h"
#include "OrbitalElement.h"

#include "KeplerOrbitScene.h"
#include "SolarObject.h"
#include "SolarObjectManager.h"

void KeplerOrbitScene::Init()
{
	const bool drawAsteroids = false;
	Time::SetTimeScale(1.f);
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

	SolarObject sun;
	sun.planetData = {1.f, 0.3f, Color::Yellow};
	sun.orbitalElement = {};

	SolarObject mercury;
	mercury.planetData = { 1.f, 0.1f, { 1.f, 0.5f, 0.f, 1.0f }};
	mercury.orbitalElement = { 0.387098f, 0.205630f, 6.35f, 48.331f, 29.124f, 174.796f };
	sun.children.push_back(mercury);

	SolarObject venus;
	venus.planetData = { 1.f, 0.15f, { 1.f, 0.83f, 0.57f, 1.0f } };
	venus.orbitalElement = { 0.723332f, 0.006772f, 2.15f, 76.680f, 54.884f, 50.115f };
	sun.children.push_back(venus);

	SolarObject earth;
	earth.planetData = { 1.f, 0.15f, Color::Blue };
	earth.orbitalElement = { 1.000003f, 0.0167086f, 0.00005f, -11.26064f, 114.20783f, 358.617f };
	sun.children.push_back(earth);

	SolarObject moon;
	moon.planetData = { 1.f, 0.01f, Color::White};
	moon.orbitalElement = { 0.1f, 0.0167086f, 0.00005f, -11.26064f, 114.20783f, 358.617f };
	earth.children.push_back (moon);

	SolarObject mars;
	mars.planetData = { 1.f, 0.1f, Color::Red };
	mars.orbitalElement = { 1.52371f, 0.0934f, 1.63f, 49.57854f, 286.5f, 19.412f };
	sun.children.push_back(mars);

	SolarObject jupiter;
	jupiter.planetData = { 1.f, 0.89f, { 1.f, 0.8f, 0.6f, 1.0f } };
	jupiter.orbitalElement = { 5.2029f, 0.0489f, 0.32f, 100.464f, 273.867f, 20.020f };
	sun.children.push_back(jupiter);

	SolarObject saturn;
	saturn.planetData = { 1.f, 0.74f, { 1.f, 1.f, 0.6f, 1.0f } };
	saturn.planetData.rings = { 0.4f, 0.42f, 0.43f, 0.46f, 0.48f, 0.51f, 0.53f, 0.55f };
	saturn.orbitalElement = { 9.537f, 0.0565f, 0.93f, 113.665f, 339.392f, 317.020f };
	sun.children.push_back(saturn);

	SolarObject uranus;
	uranus.planetData = { 1.f, 0.32f, { 0.47f, 0.78f, 0.8f, 1.0f } };
	uranus.orbitalElement = { 19.189f, 0.04717f, 0.99f, 74.006f, 96.998857f, 142.238600f };
	sun.children.push_back(uranus);

	SolarObject neptun;
	neptun.planetData = { 1.f, 0.31f, { 0.57f, 0.8f, 0.94f, 1.0f } };
	neptun.orbitalElement = { 30.0699f, 0.008678f, 0.74f, 131.783f, 273.187f, 259.883f };
	sun.children.push_back(neptun);

	SolarObject pluto;
	neptun.planetData = { 1.f, 0.05f, { 0.4f, 0.34f, 0.30f, 1.0f } };
	neptun.orbitalElement = { 39.482f, 0.2488f, 17.16f, 110.299f, 113.834f, 14.53f };
	sun.children.push_back(neptun);

	SpawnSolarObjects(sun);

	auto som = AddGameObject()->AddComponent<SolarObjectManager>();
	som->SetSolarObject(sun);

	////Kupier Belt
	//if (drawAsteroids)
	//{
	//	std::random_device rd; // obtain a random number from hardware
	//	std::mt19937 gen(rd()); // seed the generator
	//	std::uniform_int_distribution<> smaRnd(25, 35); // define the range
	//	std::uniform_int_distribution<> eRnd(0, 5); // define the range
	//	std::uniform_int_distribution<> iRnd(-10, 10); // define the range
	//	std::uniform_int_distribution<> oRnd(0, 360); // define the range
	//	std::uniform_int_distribution<> wRnd(0, 360); // define the range

	//	for (int j = 0; j < 300; ++j)
	//	{
	//		float sma = smaRnd(gen) * 0.1f;
	//		float e = eRnd(gen) * 0.1f;
	//		float i = float (iRnd(gen));
	//		float o = float (oRnd(gen));
	//		float w = float (wRnd(gen));

	//		PlanetData asteroid{ 1.f, 0.025f, { 0.3f, 0.3f, 0.3f, 1.0f }, false, {sma, e, i, o, w}, 0, 0.05f };
	//		AddPlanet (asteroid, soi);
	//	}
	//}

	////Outer belt
	//if (drawAsteroids)
	//{
	//	std::random_device rd; // obtain a random number from hardware
	//	std::mt19937 gen(rd()); // seed the generator
	//	std::uniform_int_distribution<> smaRnd(350, 400); // define the range
	//	std::uniform_int_distribution<> eRnd(0, 5); // define the range
	//	std::uniform_int_distribution<> iRnd(-10, 10); // define the range
	//	std::uniform_int_distribution<> oRnd(0, 360); // define the range
	//	std::uniform_int_distribution<> wRnd(0, 360); // define the range
	//	std::uniform_int_distribution<> sizeRnd(25, 200); // define the range

	//	for (int j = 0; j < 1000; ++j)
	//	{
	//		float sma = smaRnd(gen) * 0.1f;
	//		float e = eRnd(gen) * 0.1f;
	//		float i = float (iRnd(gen));
	//		float o = float (oRnd(gen));
	//		float w = float (wRnd(gen));
	//		float size = sizeRnd (gen) * 0.001f;

	//		PlanetData star{ 1.f, size, { 0.3f, 0.3f, 0.3f, 1.0f }, false, {sma, e, i, o, w}, 0, 0.05f };
	//		AddPlanet(star, soi);
	//	}
	//}
}

void KeplerOrbitScene::SpawnSolarObjects(SolarObject& root)
{
	auto planet = AddGameObject();

	auto renderer = planet->AddComponent<MeshRenderer>();
	renderer->SetMesh(Mesh::Sphere(16, 16));
	auto mat = std::make_shared<ColorMaterial>();
	mat->SetColor(root.planetData.color);
	renderer->SetMaterial(mat);

	float scale = root.planetData.radius;
	planet->transform.SetLocalScale({ scale, scale, scale });

	if (root.planetData.rings.size() > 0)
	{
		auto rings = planet->AddComponent<PlanetRings>();
		rings->SetColor (root.planetData.color);
		rings->SetRings (root.planetData.rings);
	}

	root.gameObject = planet;

	for (size_t i = 0; i < root.children.size(); ++i)
		SpawnSolarObjects (root.children[i]);
}
