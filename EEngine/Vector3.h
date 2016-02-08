#pragma once

namespace EEngine
{
	class Vector3
	{
	public:
		Vector3();
		Vector3(float x, float y, float z);
		~Vector3();

		float x;
		float y;
		float z;
	};
}