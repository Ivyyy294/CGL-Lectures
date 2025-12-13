#pragma once
#include <IvyyyComponent.h>
#include <vector>
#include "PrefabButton.h"

using namespace Ivyyy;

class ButtonController
	: public Component
{
public:
	ButtonController ();
	void AddButton (PrefabButton* button);
	void Update () override;

	void ActivateButton (const size_t index, const std::wstring& label);
	void DisableButton (const size_t index);

	size_t ButtonCount () const { return buttonVec.size (); }
private:
	std::vector <PrefabButton*> buttonVec;
};

