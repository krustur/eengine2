#pragma once

#include "Transform.h"

namespace EEngine
{
	class GameObject
	{
	public:
		explicit GameObject();
		~GameObject();

		DirectX::XMMATRIX &GetLocalTransform();
		DirectX::XMMATRIX &GetWorldTransform();
		DirectX::XMMATRIX &GetInversedLocalTransform();

		Vector3 &GetPosition();
		Vector3 &GetRotation();
		Vector3 &GetScale();

		void SetPosition(Vector3 &position);
		void SetRotation(Vector3 &rotation);
		void SetScale(Vector3 &scale);

	private:
		Transform _transform;
	};
}