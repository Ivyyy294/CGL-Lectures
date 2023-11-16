#pragma once

#include <IvyyyFontMesh.h>
#include <IvyyyComponent.h>
#include <stack>
#include "ButtonController.h"
#include "PrefabDrawing.h"
#include "PageGraph.h"

using namespace Ivyyy;

class PageController : public Component
{
public:
	PageController ();
	void Start () override;
	void Update () override;

	FontMesh* textMesh { nullptr };
	PrefabDrawing* prefabDrawing {nullptr};
	ButtonController* buttonController{ nullptr };

private:
	PageGraph pageGraph;
	std::stack <PageNode::Ptr> pageHistory;
	PageNode::Ptr currentPage{ nullptr };
	PageNode::Ptr nextPage{ nullptr };

	void InitPageGraph ();
	void LoadPage (PageNode::Ptr page);

	void SetAnswer (int index);

	void OnAnswer1 ();
	void OnAnswer2 ();
	void OnAnswer3 ();
	void OnAnswer4 ();

	void OnExit ();
	void OnBack ();
	void OnReset ();

};
