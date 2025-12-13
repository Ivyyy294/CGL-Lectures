#pragma once
#include "IvyyyComponent.h"
#include "IvyyyFontMesh.h"
#include "IvyyyColor.h"

class AnswerButton :
	public Ivyyy::Component
{
public:
	void Start () override;

	void OnMouseDown () override;
	void OnMouseEnter () override;
	void OnMouseExit () override;

	inline void SetEvent (const std::string& _event) { event = _event;}
private:
	float timer{ 0.f };
	Ivyyy::FontMesh* fontMesh;
	std::string event;
	Ivyyy::Color colorHover;
	Ivyyy::Color colorDefault;
};

