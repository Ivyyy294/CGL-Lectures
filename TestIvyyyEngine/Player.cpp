#include "Player.h"
#include "IvyyyRectCollider.h"
#include "IvyyySpriteMesh.h"
#include "PlayerMovement.h"
#include "IvyyyPhysicObject.h"
#include "IvyyyCircleCollider.h"

using namespace Ivyyy;

Player::Player ()
{
	AddComponent<SpriteMesh> ()->SetFilePath (L"player.png");
	//AddComponent<RectCollider> ()->SetSize (96.f, 96.f);
	AddComponent<CircleCollider> ()->SetRadius (96.f * 0.5f);
	AddComponent<PlayerMovement> ();
	AddComponent<PhysicObject>()->SetLinearDamping (0.0f);
}
