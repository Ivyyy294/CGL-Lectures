#include "KeplerOrbitScene.h"
#include "IvyyyDirectionalLight.h"
#include "DebugInfo.h"
#include "IvyyyMeshRenderer.h"
#include "IvyyyTextureShaderClass.h"
#include "PlayerMovement.h"

void KeplerOrbitScene::Init()
{
	//Add Light
	auto light = AddGameObject<GameObject>()->AddComponent<DirectionalLight>();
	light->SetColor(Color(1.f, 1.f, 1.f, 0.5f));

	//UI
	auto ui = AddGameObject();
	ui->transform.SetPosition(Vector3(0.f, 0.f, 0.0f));
	ui->transform.SetPivot(Transform::Pivot::TOPLEFT);
	ui->transform.SetSpace(Transform::Space::SCREEN);

	auto fontRenderer = ui->AddComponent<FontRenderer>();
	fontRenderer->SetText(L"Hello World!");
	fontRenderer->SetSize(Vector2(512.f, 100.f));

	//Grid
	auto grid = AddGameObject();
	grid->transform.SetLocalScale ({10.f, 10.f, 10.f});
	grid->transform.SetRotation (Quaternion::Euler(-5.f, 0.f, 0.f) * Quaternion::Euler(0.f, 45.f, 0.f));


	//grid->AddComponent<PlayerMovement>();

	auto mr = grid->AddComponent<MeshRenderer>();
	mr->SetMesh(Mesh::CornerGrid());
	
	auto mat = std::make_shared<TextureShaderClass>();
	mat->SetTexture (Texture::LoadTexture(L"texture_test.png"));
	mr->SetMaterial(mat);

	ui->AddComponent <DebugInfo>();

	//Camera
	Camera::MainCamera()->GetTransform()->SetPosition ({0.f, -1.f, -20.f});
	//Camera::MainCamera()->GetTransform()->SetRotation (Quaternion::Euler(5.f, -5.f, 0.f));
}
