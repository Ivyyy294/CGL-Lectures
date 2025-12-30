#include "D3DTestScene.h"
#include "IvyyyMeshRenderer.h"
#include "IvyyyMesh.h"
#include "ColorShader.h"
#include "PlayerMovement.h"
#include "IvyyyCamera.h"
#include "IvyyyTextureShaderClass.h"
#include "IvyyyDirectionalLight.h"
#include "IvyyySpriteRenderer.h"
#include "IvyyyRectCollider.h"
#include "IvyyyPhysicObject.h"
#include"DebugInfo.h"

void D3DTestScene::Init()
{
	InitColorCubes();
	//InitTextureCubes();
	//InitSpriteCubes();

	//Add Debug Object
	auto debug = AddGameObject <GameObject>(Vector2(0, 64));
	debug->transform.SetSpace(Transform::Space::SCREEN);
	debug->transform.SetPivot(Transform::Pivot::TOPLEFT);
	debug->AddComponent<DebugInfo>();

	//Texture::Ptr texture = Texture::LoadTexture(L"player.png");
	//TextureShaderClass* textureShader = new TextureShaderClass;
	//textureShader->SetTexture(texture);

	//meshRenderer->SetMaterial (textureShader);

	////Child cube
	//Texture::Ptr texture2 = Texture::LoadTexture(L"stone01.tga");
	//auto childCube = AddGameObject<GameObject>(&parentCube->transform, Vector3(-10.f, 0.f, 0.f));
	//meshRenderer = childCube->AddComponent<MeshRenderer>();
	//meshRenderer->SetMesh(cube);

	//textureShader = new TextureShaderClass;
	//textureShader->SetTexture(texture2);
	//meshRenderer->SetMaterial(textureShader);

	//auto childCube2 = AddGameObject<GameObject>(&childCube->transform, Vector3(0.f, -5.f, 0.f));
	//meshRenderer = childCube2->AddComponent<MeshRenderer>();
	//meshRenderer->SetMesh(cube);
	//textureShader = new TextureShaderClass;
	//textureShader->SetTexture(texture2);
	//meshRenderer->SetMaterial(textureShader);

	//Add Light
	auto light = AddGameObject<GameObject>()->AddComponent<DirectionalLight>();
	light->SetColor(Color(1.f, 1.f, 1.f, 0.5f));
}

void D3DTestScene::InitColorCubes()
{
	//Parent cube
	auto parentCube = AddGameObject<GameObject>();
	auto meshRenderer = parentCube->AddComponent<MeshRenderer>();

	std::shared_ptr<ColorShader> colorMaterial = std::make_shared<ColorShader>();

	Mesh cube;
	cube.LoadModel("cube.txt");
	meshRenderer->SetMesh(cube);
	meshRenderer->SetMaterial (colorMaterial);
	parentCube->AddComponent<PlayerMovement>();
	parentCube->AddComponent<PhysicObject>();

	//Child cube
	auto childCube = AddGameObject<GameObject>(&parentCube->transform, Vector3(-10.f, 0.f, 0.f));
	meshRenderer = childCube->AddComponent<MeshRenderer>();
	meshRenderer->SetMesh(cube);
	meshRenderer->SetMaterial (colorMaterial);

	auto childCube2 = AddGameObject<GameObject>(&childCube->transform, Vector3(0.f, -5.f, 0.f));
	meshRenderer = childCube2->AddComponent<MeshRenderer>();
	meshRenderer->SetMesh(cube);
	meshRenderer->SetMaterial(colorMaterial);
}

void D3DTestScene::InitTextureCubes()
{
	//Parent cube
	auto parentCube = AddGameObject<GameObject>();
	auto meshRenderer = parentCube->AddComponent<MeshRenderer>();

	std::shared_ptr<TextureShaderClass> testTextureMat = std::make_shared<TextureShaderClass>();
	testTextureMat->SetTexture (Texture::LoadTexture(L"texture_test.png"));

	Mesh cube;
	cube.LoadModel("cube.txt");
	//meshRenderer->GetTransform()->SetSpace(Transform::Space::SCREEN);
	meshRenderer->SetMesh(cube);
	meshRenderer->SetMaterial(testTextureMat);
	parentCube->AddComponent<PlayerMovement>();
	parentCube->AddComponent<PhysicObject>();

	//Child cube
	auto childCube = AddGameObject<GameObject>(&parentCube->transform, Vector3(-10.f, 0.f, 0.f));
	meshRenderer = childCube->AddComponent<MeshRenderer>();
	//meshRenderer->GetTransform()->SetSpace(Transform::Space::SCREEN);
	meshRenderer->SetMesh(cube);
	meshRenderer->SetMaterial(testTextureMat);

	auto childCube2 = AddGameObject<GameObject>(&childCube->transform, Vector3(0.f, -5.f, 0.f));
	meshRenderer = childCube2->AddComponent<MeshRenderer>();
	//meshRenderer->GetTransform()->SetSpace(Transform::Space::SCREEN);
	meshRenderer->SetMesh(cube);
	meshRenderer->SetMaterial(testTextureMat);
}

void D3DTestScene::InitSpriteCubes()
{
	//Parent cube
	auto parentCube = AddGameObject<GameObject>();
	auto meshRenderer = parentCube->AddComponent<SpriteRenderer>();

	std::shared_ptr<TextureShaderClass> testTextureMat = std::make_shared<TextureShaderClass>();
	testTextureMat->SetTexture(Texture::LoadTexture(L"texture_test.png"));

	Mesh cube;
	cube.LoadModel("cube.txt");
	meshRenderer->GetTransform()->SetSpace(Transform::Space::SCREEN);
	meshRenderer->GetTransform()->SetPivot(Transform::Pivot::TOPLEFT);
	meshRenderer->SetMaterial(testTextureMat);
	parentCube->AddComponent<PlayerMovement>();
	parentCube->AddComponent<PhysicObject>();

	auto rectCollider = parentCube->AddComponent<RectCollider>();
	rectCollider->SetSize (512.f, 512.f);
}
