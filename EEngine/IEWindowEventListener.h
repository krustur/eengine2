#pragma once

#include <Windows.h>

class IEWindowEventListener
{
public:
	virtual void OnMouseDown(WPARAM buttonState, int x, int y) = 0;
	virtual void OnMouseUp(WPARAM buttonState, int x, int y) = 0;
	virtual void OnMouseMove(WPARAM buttonState, int x, int y) = 0;
};