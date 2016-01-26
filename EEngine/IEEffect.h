#pragma once
class IEEffect
{
public:
	virtual ~IEEffect() {}

	virtual void UpdateScene(float deltaTime) = 0;
	virtual void DrawScene() = 0;
	virtual void OnResize() = 0;
};

