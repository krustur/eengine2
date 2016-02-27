#pragma once

#include <DirectXMath.h>
#include "Vector3.h"

namespace EEngine
{
	class Transform
	{
	public:
		explicit Transform();
		explicit Transform(Vector3 &position, Vector3 &rotation);
		~Transform();

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
		Vector3 _position;
		Vector3 _rotation;
		Vector3 _scale;
		DirectX::XMMATRIX _localTransform;
		DirectX::XMMATRIX _inversedLocalTransform;
		//DirectX::XMMATRIX _worldTransform;
	};
}