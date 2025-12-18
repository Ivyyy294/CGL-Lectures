#include <math.h>
#include "IvyyyLine.h"
#include "IvyyyGeometryMesh.h"
#include "DebugInfo.h"
#include "IvyyyMathF.h"
#include "TreeScene.h"

void TreeScene::Init ()
{
	float angle = 23.f;
	int depth = 1;

	NodeInfo rootInfo;
	rootInfo.width = 96.f;
	rootInfo.angle = 40.f;
	rootInfo.rotation = 0.f;
	rootInfo.parent = nullptr;
	rootInfo.pos = Vector2 (0.f, -200.f);
	rootInfo.width = 100.f;
	rootInfo.color = Color (152, 107, 65);

	BuildTree (0, 14, rootInfo);

	/*auto debug = AddGameObject <GameObject>();
	debug->transform.SetSpace (Transform::Space::SCREEN);
	debug->transform.SetPivot (Transform::Pivot::TOPLEFT);
	auto fontMesh = debug->AddComponent<D2D1FontMesh> ();
	fontMesh->font.color = Color (255, 0,0 );
	fontMesh->font.height = 12;
	fontMesh->SetSize (200.f, 32.f);
	debug->AddComponent<DebugInfo> ();*/
}

void TreeScene::BuildTree (const int depth, const int maxDepth, const NodeInfo& sideInfo)
{
	if (depth < maxDepth)
	{
		ChildInfo childInfo = AddTreeNodeObject (sideInfo);

		//Dye last two Nodes pink
		if (depth + 3 == maxDepth)
		{
			Color pink (255, 183, 197);
			childInfo.left.color = pink;
			childInfo.right.color = pink;
		}

		//Call BuildTree for left and right
		BuildTree (depth + 1, maxDepth, childInfo.left);
		BuildTree (depth + 1, maxDepth, childInfo.right);
	}

	return;
}

TreeScene::ChildInfo TreeScene::AddTreeNodeObject (const NodeInfo& nodeInfo)
{
	//Add GameObject
	//Set local position, rotation and parent  from NodeInfo
	auto gameObject = AddGameObject <GameObject> (&nodeInfo.parent->transform, nodeInfo.pos, Quaternion::Euler (0.f, 0.f, -nodeInfo.rotation));

	//Add GeometryMesh component
	auto geoMesh = gameObject->AddComponent <GeometryMesh> ();

	//Set Mesh color
	geoMesh->color = nodeInfo.color;

	Vector3 vertices[7];

	//Rect containts of P1, P2, P6 and P7 
	vertices[0] = Vector2 (nodeInfo.width * -0.5f, 0.0f);
	vertices[1] = Vector2 (vertices[0].x, nodeInfo.width);
	vertices[5] = Vector2 (nodeInfo.width * 0.5f, nodeInfo.width);
	vertices[6] = Vector2 (vertices[5].x, 0.0f);

	//Triangle consists of P2, P4, P6 and sub positions P3 and P5

	//Length ankathete
	float widhtLeft = nodeInfo.width * cosf (nodeInfo.angle * MathF::Deg2Rad);
	//Length gegenkathete
	float widhtRight = nodeInfo.width * sinf (nodeInfo.angle * MathF::Deg2Rad);
	
	//Calculate P3-P5
	vertices[2] = GetLineEndPos (vertices[1], widhtLeft * 0.5f, nodeInfo.angle);
	vertices[3] = GetLineEndPos (vertices[1], widhtLeft, nodeInfo.angle);
	vertices[4] = GetLineEndPos (vertices[5], widhtRight * 0.5f,  90.0f + nodeInfo.angle);

	//Add points to GeometryMesh
	geoMesh->m_mesh.SetVertices (vertices, 7);

	//Set index list
	unsigned long indices[] {0, 1, 2, 3, 4, 5, 6};
	geoMesh->m_mesh.SetIndices(indices, 7);

	//Set Child Info struct
	ChildInfo childInfo;
	childInfo.left.angle = nodeInfo.angle;
	childInfo.left.color = nodeInfo.color;
	childInfo.left.parent = gameObject.get();
	childInfo.left.width = widhtLeft;
	childInfo.left.pos = vertices[2];
	childInfo.left.rotation = -nodeInfo.angle;

	childInfo.right.angle = nodeInfo.angle;
	childInfo.right.color = nodeInfo.color;
	childInfo.right.parent = gameObject.get ();
	childInfo.right.width = widhtRight;
	childInfo.right.pos = vertices[4];
	childInfo.right.rotation = 90.f - nodeInfo.angle;
	return childInfo;
}

Vector2 TreeScene::GetLineEndPos (const Vector2& startPos, const float width, const float angle) const
{
	Line line (startPos, startPos + Vector2 (width, 0.f));
	line.SetAngle (line.Angle() + angle);
	return line.P2 ();
}
