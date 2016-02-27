#include "Transform.h"

namespace EEngine
{
	Transform::Transform() : 
		_position(0, 0, 0),
		_rotation(0, 0, 0),
		_scale(1, 1, 1),
		_localTransform(DirectX::XMMatrixIdentity())
	{
	}

	Transform::Transform(Vector3 &position, Vector3 &rotation) :
		_position(position),
		_rotation(rotation),
		_scale(1, 1, 1)
	{
	}

	Transform::~Transform()
	{
	}

	DirectX::XMMATRIX &Transform::GetLocalTransform()
	{
		DirectX::XMMATRIX scaleMatrix = DirectX::XMMatrixScaling(_scale.x, _scale.y, _scale.z);
		DirectX::XMMATRIX rotationMatrixX = DirectX::XMMatrixRotationX(_rotation.x);
		DirectX::XMMATRIX rotationMatrixY = DirectX::XMMatrixRotationY(_rotation.y);
		DirectX::XMMATRIX rotationMatrixZ = DirectX::XMMatrixRotationZ(_rotation.z);
		DirectX::XMMATRIX translateMatrix = DirectX::XMMatrixTranslation(_position.x, _position.y, _position.z);

		_localTransform = scaleMatrix * rotationMatrixX * rotationMatrixY * rotationMatrixZ * translateMatrix;

		return _localTransform;
	}

	DirectX::XMMATRIX &Transform::GetWorldTransform()
	{
		return GetLocalTransform();
	}

	DirectX::XMMATRIX &Transform::GetInversedLocalTransform()
	{
		DirectX::XMMATRIX localTransform = GetLocalTransform();

		_inversedLocalTransform = DirectX::XMMatrixInverse(nullptr, localTransform);

		return _inversedLocalTransform;
	}

	Vector3 &Transform::GetPosition()
	{
		return _position;
	}

	Vector3 &Transform::GetRotation()
	{
		return _rotation;
	}

	Vector3 &Transform::GetScale()
	{
		return _scale;
	}

	void Transform::SetPosition(Vector3 &position)
	{
		_position = position;	
	}

	void Transform::SetRotation(Vector3 &rotation)
	{
		_rotation = rotation;
	}

	void Transform::SetScale(Vector3 &scale)
	{
		_scale = scale;
	}
}