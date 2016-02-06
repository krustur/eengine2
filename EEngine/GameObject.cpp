#include "GameObject.h"


namespace EEngine
{
	GameObject::GameObject() :
		_position(0, 0, 0),
		_rotation(0, 0, 0),
		_scale(1, 1, 1)		
	{
	}

	GameObject::GameObject(float x, float y, float z, float xRot, float yRot, float zRot) :
		_position(x, y, z),
		_rotation(xRot, yRot, zRot),
		_scale(1, 1, 1)
	{
	}

	GameObject::~GameObject()
	{
	}

	DirectX::XMMATRIX &GameObject::GetLocalTransform()
	{
		DirectX::XMMATRIX scaleMatrix = DirectX::XMMatrixScaling(_scale.x, _scale.y, _scale.z);
		DirectX::XMMATRIX rotationMatrixX = DirectX::XMMatrixRotationX(_rotation.x);
		DirectX::XMMATRIX rotationMatrixY = DirectX::XMMatrixRotationY(_rotation.y);
		DirectX::XMMATRIX rotationMatrixZ = DirectX::XMMatrixRotationZ(_rotation.z);
		DirectX::XMMATRIX translateMatrix = DirectX::XMMatrixTranslation(_position.x, _position.y, _position.z);

		DirectX::XMMATRIX transform = scaleMatrix * rotationMatrixX * rotationMatrixY * rotationMatrixZ * translateMatrix;

		return transform;
	}
	
	DirectX::XMMATRIX &GameObject::GetWorldTransform()
	{
		return GetLocalTransform();
	}
	
	DirectX::XMMATRIX &GameObject::GetInversedLocalTransform()		
	{
		DirectX::XMMATRIX localTransform = GetLocalTransform();
		
		DirectX::XMMATRIX inversedLocalTransform = DirectX::XMMatrixInverse(nullptr, localTransform);

		return inversedLocalTransform;
	}

	DirectX::XMFLOAT3 &GameObject::GetPosition()
	{
		return _position;
	}

	DirectX::XMFLOAT3 &GameObject::GetRotation()
	{
		return _rotation;
	}

	DirectX::XMFLOAT3 &GameObject::GetScale()
	{
		return _scale;
	}

	void GameObject::SetPosition(DirectX::XMFLOAT3 &position)
	{
		_position = position;
	}

	void GameObject::SetRotation(DirectX::XMFLOAT3 &rotation)
	{
		_rotation = rotation;
	}

	void GameObject::SetScale(DirectX::XMFLOAT3 &scale)
	{
		_scale = scale;
	}

}