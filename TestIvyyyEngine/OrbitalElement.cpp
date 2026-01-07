#include "OrbitalElement.h"
#include "IvyyyMathF.h"
#include <cmath>
#include "IvyyyDraw.h"
#include "IvyyyTime.h"

void OrbitalElement::Update()
{
	if (m_rb == nullptr)
	{
		m_rb = gameObject->GetComponent<PhysicObject>().get();

		if (m_rb == nullptr)
			return;

		CalculateOrbit();
		//CalculateOrbitPath();
	}

	//if (m_timer >= m_t)
	//{
	//	CalculateOrbitPath();
	//	m_timer = 0.f;
	//}
	//else
	//	m_timer += Time::DeltaTime();

	//for (int i = 1; i < 16; ++i)
	//	Draw::AddLine(m_orbitPath[i - 1], m_orbitPath[i], Color::White);

	//Draw::AddLine(m_orbitPath[0], m_orbitPath[16 - 1], Color::White);
}

void OrbitalElement::SetOrbitalData(const OrbitalElementData& orbitData, const PhysicObject* soi)
{
	m_orbitData = orbitData;
	m_soi = soi;
}

void OrbitalElement::CalculateOrbit()
{
	//Apply Longitude of ascending node
	Vector3 ascendingNodeDir = Vector3::Down;
	m_orbitalPlaneNormal = Vector3::Back;

	Quaternion o = Quaternion::AroundAxis(Vector3::Forward, m_orbitData.o * MathF::Deg2Rad);

	ascendingNodeDir = (o * ascendingNodeDir).Normalized();

	m_orbitalPlaneNormal = o * m_orbitalPlaneNormal;

	//Apply inclination
	Quaternion i = Quaternion::AroundAxis(ascendingNodeDir, -m_orbitData.i * MathF::Deg2Rad);

	m_orbitalPlaneNormal = (i * m_orbitalPlaneNormal).Normalized();

	m_periapsisDir = m_orbitalPlaneNormal.Cross(ascendingNodeDir);

	//Apply Argument of periapsis
	Quaternion w = Quaternion::AroundAxis(m_orbitalPlaneNormal, -m_orbitData.w * MathF::Deg2Rad);

	m_periapsisDir = (w * m_periapsisDir).Normalized();

	//Callculate velocity

	m_c = m_orbitData.e * m_orbitData.a;

	if (m_c > 0.f)
		m_b = sqrt (m_orbitData.a * m_orbitData.a - m_c * m_c);
	else
		m_b = m_orbitData.a;

	Vector3 f1 = m_soi->GetTransform()->GetPosition();

	m_center = f1 - m_periapsisDir * m_c;

	Vector3 v1 = m_center + (m_periapsisDir * m_orbitData.a);

	float r = (v1 - f1).Magnitude();

	float v = sqrtf((m_soi->GetMass()) * (2.f / r - 1.f / m_orbitData.a));

	Vector3 velDir = m_periapsisDir.Cross(m_orbitalPlaneNormal);
	Vector3 velocity = velDir * v;

	Vector3 orbitPlaneNormal = ascendingNodeDir.Cross(m_periapsisDir);

	transform->SetPosition(v1);

	m_rb->SetVelocity(velocity);

	m_t = 2.f * M_PI * sqrtf(pow (m_orbitData.a, 3.f) / m_soi->GetMass());
}

void OrbitalElement::CalculateOrbitPath()
{
	Vector3 u = (m_center - transform->GetPosition()).Normalized();
	Vector3 v = u.Cross(m_orbitalPlaneNormal);

	const double TWO_PI = 2.0 * M_PI;

	for (int i = 0; i < 16; ++i)
	{
		double theta = TWO_PI * i / 16;

		Vector3 point =
			m_center +
			v * (m_orbitData.a * std::cos(theta)) +
			u * (m_b * std::sin(theta));

		m_orbitPath[i] = point;
	}
}
