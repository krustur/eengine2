#pragma once

#include "Transform.h"

namespace EEngine
{
	class GameObject
	{
	public:
		explicit GameObject();
		~GameObject();

		Transform &GetTransform();


	private:
		Transform _transform;
	};
}