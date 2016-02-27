#include "GameObject.h"


namespace EEngine
{
	GameObject::GameObject() :
		_transform()
	{
	}

	GameObject::~GameObject()
	{
	}

	DirectX::XMMATRIX &GameObject::GetLocalTransform()
	{
		return _transform.GetLocalTransform();
	}

	DirectX::XMMATRIX &GameObject::GetWorldTransform()
	{
		return _transform.GetWorldTransform();
	}

	DirectX::XMMATRIX &GameObject::GetInversedLocalTransform()
	{
		return _transform.GetInversedLocalTransform();
	}

	Vector3 &GameObject::GetPosition()
	{
		return _transform.GetPosition();
	}

	Vector3 &GameObject::GetRotation()
	{
		return _transform.GetRotation();
	}

	Vector3 &GameObject::GetScale()
	{
		return _transform.GetScale();
	}

	void GameObject::SetPosition(Vector3 &position)
	{
		_transform.SetPosition(position);
	}

	void GameObject::SetRotation(Vector3 &rotation)
	{
		_transform.SetRotation(rotation);
	}

	void GameObject::SetScale(Vector3 &scale)
	{
		_transform.SetScale(scale);
	}
}