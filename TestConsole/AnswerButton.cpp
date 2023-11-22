#include "AnswerButton.h"
#include "IvyyyTime.h"
#include "IvyyyEventSystem.h"

using namespace Ivyyy;

void AnswerButton::Start ()
{
	colorHover = Color (0, 255, 0);
	colorDefault = Color (255, 255, 255);

	fontMesh = gameObject->GetComponent<FontMesh> ().get();
	fontMesh->font.color = colorDefault;
}

void AnswerButton::OnMouseDown ()
{
	if (!event.empty ())
		EventSystem::Me ()->Event (event).Invoke ();
}

void AnswerButton::OnMouseEnter ()
{
	fontMesh->font.color = colorHover;
}

void AnswerButton::OnMouseOver ()
{
	if (fontMesh->font.color != colorHover)
		fontMesh->font.color = colorHover;
}

void AnswerButton::OnMouseExit ()
{
	fontMesh->font.color = colorDefault;
}



