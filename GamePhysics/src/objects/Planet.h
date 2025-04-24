#include "GameObject.h"
#include "PhysicObject.h"
#include <imgui.h>

class Planet
: public PhysicObject
{
public:
	Planet (float radius, float mass, ImColor color = ImColor (1.0f, 1.0f, 1.0f, 1.0f));
	~Planet(){};

	static float m_universalGravitationalConstant;
	static float m_ScaleOneTo;
	
	Collision TestCollision(PhysicObject* collider) override;
private:
	float m_radius;
	ImColor m_color;

	void Draw() override;
	void Update(float deltaTime) override{};

	float GetScale();

	virtual void OnCollisionEnter(PhysicObject* obj, const Collision& collision) override;
};
