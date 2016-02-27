#include "Vector3.h"

namespace EEngine
{
	Vector3::Vector3()
	{
	}

	Vector3::Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3::Vector3(const Vector3 &other)
	{ 
		x = other.x;
		y = other.y;
		z = other.z;
	}

	Vector3 & Vector3::operator=(const Vector3 & other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	Vector3::~Vector3()
	{
	}
}