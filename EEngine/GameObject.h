#pragma once

#include <DirectXMath.h>

namespace EEngine
{
	class GameObject
	{
	public:
		GameObject();
		GameObject(float x, float y, float z, float xRot, float yRot, float zRot);
		~GameObject();

		DirectX::XMMATRIX GetLocalTransform();
		DirectX::XMMATRIX GetWorldTransform();
		DirectX::XMMATRIX GetInversedLocalTransform();

	private:
		DirectX::XMFLOAT3 _position;
		DirectX::XMFLOAT3 _rotation;
		DirectX::XMFLOAT3 _scale;
	};
}