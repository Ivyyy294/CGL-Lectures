#pragma once

#include <IvyyyVector3.h>
#include <IvyyyColor.h>

using namespace Ivyyy;

class ReferenceFrame
{
	//Variables
	private:
		Vector3 m_position = Vector3::Zero;
		Vector3 m_velocity = Vector3::Zero;
		Vector3 m_up = Vector3::Up;
		Vector3 m_forward = Vector3::Forward;
		Vector3 m_right = Vector3::Right;

	//Methods
	public:
		void Draw();

		ReferenceFrame& operator*= (const float rhs);

	private:
		void DrawAxis (const Vector3& pos, const Vector3& direction, const Color& color);
};

