#include "LoadingText.h"
#include "IvyyyTime.h"
#include "IvyyyInput.h"
#include "IvyyySceneHandler.h"

void LoadingText::Start ()
{
	fontMesh = gameObject->GetComponent <FontMesh> ().get();

	welcome.SetText (L"•••• <<<< Welcome to Medina station>>>> ••••", 30);
	pressEnter.SetText (L"[Press enter to continue...]", 30);
	fontMesh->SetSize (400.f, 100.f);
	fontMesh->font.family = L"Consolas";
	fontMesh->font.height = 16;
	fontMesh->font.alignment = Font::VERTICAL_CENTER | Font::HORIZONTAL_TOP;
	transform->SetSpace (Transform::Space::SCREEN);
}

void LoadingText::Update ()
{
	welcome.Update ();
	std::wstring content = welcome.GetCurrentText();

	if (welcome.Done ())
	{
		content += L"\n\n";

		if (percent <= 100)
		{
			content += L"<<<< Loading " + std::to_wstring (percent) + L"% >>>>";
			timer += Time::DeltaTime ();
			percent = (int)std::abs((timer * 1000.f) / 16.f);
		}
		else
		{
			content += L"<<<< Complete! >>>>";

			pressEnter.Update ();
			content += L"\n\n" + pressEnter.GetCurrentText ();
		}
	}

	fontMesh->text = content;

	if (pressEnter.Done () && Input::KeyPressed (Key::KEY_RETURN))
		SceneHandler::LoadScene (1);
}
