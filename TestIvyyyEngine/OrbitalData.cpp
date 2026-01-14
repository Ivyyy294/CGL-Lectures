#include "OrbitalData.h"
#include <IvyyyMathF.h>
#include <IvyyyQuaternion.h>

OrbitalData::OrbitalData(const OrbitalElementData& data)
{
	//Apply Longitude of ascending node
	Vector3 ascendingNodeDir = Vector3::Down;
	Vector3 orbitalPlaneNormal = Vector3::Back;

	Quaternion o = Quaternion::AroundAxis(Vector3::Forward, data.o * MathF::Deg2Rad);

	ascendingNodeDir = (o * ascendingNodeDir).Normalized();

	orbitalPlaneNormal = o * orbitalPlaneNormal;

	//Apply inclination
	Quaternion i = Quaternion::AroundAxis(ascendingNodeDir, -data.i * MathF::Deg2Rad);

	orbitalPlaneNormal = (i * orbitalPlaneNormal).Normalized();

	Vector3 periapsisDir = orbitalPlaneNormal.Cross(ascendingNodeDir);

	//Apply Argument of periapsis
	Quaternion w = Quaternion::AroundAxis(orbitalPlaneNormal, -data.w * MathF::Deg2Rad);

	periapsisDir = (w * periapsisDir).Normalized();

	c = data.e * data.a;

	if (c > 0.f)
		b = sqrt(data.a * data.a - c * c);
	else
		b = data.a;

	center = periapsisDir * c;

	Quaternion q_o = Quaternion::AroundAxis(Vector3::Forward, data.o * MathF::Deg2Rad);
	Quaternion q_i = Quaternion::AroundAxis(Vector3::Up, data.i * MathF::Deg2Rad);
	Quaternion q_w = Quaternion::AroundAxis(Vector3::Forward, data.w * MathF::Deg2Rad);

	orientation = (q_o * q_i * q_w);
}
