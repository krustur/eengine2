#pragma once

namespace EEngine
{
	class Vector3
	{
	public:
		Vector3();
		explicit Vector3(float x, float y, float z);
		Vector3(const Vector3 &other);
		Vector3 & operator= (const Vector3 & other);
		
		
		~Vector3();

		float x;
		float y;
		float z;
	};
}