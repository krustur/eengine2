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

		DirectX::XMMATRIX &GetLocalTransform();
		DirectX::XMMATRIX &GetWorldTransform();
		DirectX::XMMATRIX &GetInversedLocalTransform();

		DirectX::XMFLOAT3 &GetPosition();
		DirectX::XMFLOAT3 &GetRotation();
		DirectX::XMFLOAT3 &GetScale();

		void SetPosition(DirectX::XMFLOAT3 &position);
		void SetRotation(DirectX::XMFLOAT3 &rotation);
		void SetScale(DirectX::XMFLOAT3 &scale);


	private:
		DirectX::XMFLOAT3 _position;
		DirectX::XMFLOAT3 _rotation;
		DirectX::XMFLOAT3 _scale;
	};
}