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

	Transform &GameObject::GetTransform()
	{
		return _transform;
	}

}