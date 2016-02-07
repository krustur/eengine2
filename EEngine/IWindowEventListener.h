#pragma once

#include <Windows.h>

namespace EEngine
{
	class IWindowEventListener
	{
	public:
		virtual void OnActivate() = 0;
		virtual void OnDeactivate() = 0;
		virtual void OnMouseDown(WPARAM buttonState, int x, int y) = 0;
		virtual void OnMouseUp(WPARAM buttonState, int x, int y) = 0;
		virtual void OnMouseMove(WPARAM buttonState, int x, int y) = 0;
		virtual void OnResize(int width, int height) = 0;
	};
}