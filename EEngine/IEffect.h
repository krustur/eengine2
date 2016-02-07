#pragma once

namespace EEngine
{
	class IEffect
	{
	public:
		virtual ~IEffect() {}

		virtual void UpdateScene(float deltaTime) = 0;
		virtual void DrawScene() = 0;
		virtual void OnResize() = 0;
	};
}